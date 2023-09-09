#pragma once

#include <chrono>
#include <cstdint>

namespace bast {
namespace base {

/**
 * @brief 分布式id生成类
 * https://segmentfault.com/a/1190000011282426
 * https://github.com/twitter/snowflake/blob/snowflake-2010/src/main/scala/com/twitter/service/snowflake/IdWorker.scala
 *
 * 64bit id: 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000  0000
 *           ||                                                           ||     ||     |  |              |
 *           |└---------------------------时间戳--------------------------┘└中心-┘└机器-┘  └----序列号----┘
 *           |
 */

class snowflake
{
public:
    /**
     * ctor
     * @param data_center
     * @param work_id
     */
    snowflake(std::uint32_t data_center = 0, std::uint32_t work_id = 0)
    {
        if (work_id > max_work_id || work_id < 0)
        {
            throw std::runtime_error("worker Id can't be greater than 31 or less than 0");
        }

        if (data_center < max_data_center_id || data_center < 0)
        {
            throw std::runtime_error("datacenter Id can't be greater than 31 or less than 0");
        }

        this->data_center_ = data_center;
        this->work_id_ = work_id;
    }

    /**
     * snowflake id
     * @return id
     */
    std::uint64_t id()
    {
        auto timestamp = get_current_millisecond();
        if (timestamp < last_timestamp_)
        {
            throw std::runtime_error("clock moved forward. refusing to generate id");
        }

        if (last_timestamp_ == timestamp)
        {
            sequence_ = (sequence_ + 1) & sequence_mask;
            if (sequence_ == 0)
            {
                timestamp = wait_next_millisecond(last_timestamp_);
            }
        }
        else
        {
            sequence_ = 0;
        }

        last_timestamp_ = timestamp;
        return ((timestamp - twepoch) << timestamp_left_shift)
            | (data_center_ << data_center_id_shift)
            | (work_id_ << worker_id_shift)
            | sequence_;
    }

protected:
    snowflake(const snowflake &) = delete;
    snowflake &operator=(const snowflake &) = delete;

    std::uint64_t get_current_millisecond() const
    {
        auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
        return now.time_since_epoch().count();
    }

    std::uint64_t wait_next_millisecond(std::uint64_t last_timestamp) const
    {
        auto timestamp = get_current_millisecond();
        while (timestamp <= last_timestamp)
        {
            timestamp = get_current_millisecond();
        }
        return timestamp;
    }

private:
    std::uint32_t work_id_;
    std::uint32_t data_center_;

    std::int64_t sequence_{0};
    std::int64_t last_timestamp_{0};

    static constexpr std::int64_t twepoch = 1514736000000;
    static constexpr std::uint8_t worker_id_bits = 5;
    static constexpr std::uint8_t data_center_id_bits = 5;
    static constexpr std::uint8_t sequence_bits = 12;

    static constexpr std::uint8_t worker_id_shift = sequence_bits;
    static constexpr std::uint8_t data_center_id_shift = sequence_bits + worker_id_bits;
    static constexpr std::uint8_t timestamp_left_shift = sequence_bits + worker_id_bits + data_center_id_bits;
    static constexpr std::uint32_t sequence_mask = -1 ^ (-1 << sequence_bits);

    static constexpr std::uint32_t max_data_center_id = -1 ^ (-1 << data_center_id_bits);
    static constexpr std::uint32_t max_work_id = -1 ^ (-1 << worker_id_bits);
};

} // namespace base
} // namespace bast