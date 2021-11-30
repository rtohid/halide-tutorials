#include <Halide.h>
#include <HalideRuntime.h>

#include <hpx/hpx_init.hpp>
#include <hpx/iostream.hpp>
#include "apex_api.hpp"

#include <hpx/include/parallel_for_loop.hpp>
extern "C" int hpx_halide_do_task(void *ctx, halide_task_t f, int idx, uint8_t *closure) {
    apex::scoped_timer _hpx_task(__func__);

    return 0;
}

extern "C" int hpx_halide_do_par_for(void *ctx, int (*f)(void *, int, uint8_t *),
                              int min, int extent, uint8_t *closure) {
    apex::scoped_timer _hpx_par(__func__);
//    hpx::for_loop(hpx::execution::par, min, min + extent,
//                  [&](int i) { hpx_halide_do_task(ctx, f, i, closure); });
    hpx::for_loop(hpx::execution::par, min, min + extent,
                [&](int i) { f(ctx, i, closure); });
  return 0;
}



///////////////////////////////////////////////////////////////////////////
// Allow applications to add configuration settings if HPX_MAIN is set
std::vector<std::string>(*prev_user_main_config_function)(
    std::vector<std::string> const&) = nullptr;

std::vector<std::string> user_main_config(
    std::vector<std::string> const& config)
{
    // register halide custom handlers
    halide_set_custom_do_par_for(&hpx_halide_do_par_for);
    halide_set_custom_do_task(&hpx_halide_do_task);

    // If there was another config function registered, call it
    if (prev_user_main_config_function)
    {
        return prev_user_main_config_function(config);
    }
    return config;
}

// Make sure our configuration information is injected into the startup
// procedure
struct register_user_main_config
{
    register_user_main_config()
    {
        prev_user_main_config_function =
            hpx_startup::user_main_config_function;
        hpx_startup::user_main_config_function = &user_main_config;
    }
} cfg;
