#include "wait_for.hpp"

namespace sabre
{

    bool WaitFor::_done(bool result, uint64_t total_runtime)
    {
        _runtime = total_runtime;
        _result = result;
        return result;
    }

    WaitFor::WaitFor(WaitForPred fn, uint64_t timeout_in_ms,
                     uint64_t sleep_time)
        : _timeout_in_ms(timeout_in_ms), _fn(fn), _sleep_time(sleep_time)
    {
    }

    bool WaitFor::operator()()
    {
        uint64_t starttime = _get_current_time();

        while (_timeout_in_ms > _get_current_time() - starttime)
        {
            if (_fn())
                return _done(true, _get_current_time() - starttime);
            _sleep();
        }
        return _done(false, _get_current_time() - starttime);
    }

    bool WaitFor::get_result() const
    {
        return _result;
    }

    uint64_t WaitFor::get_result_runtime() const
    {
        return _runtime;
    }
}; // namespace sabre