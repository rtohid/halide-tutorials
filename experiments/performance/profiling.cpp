#include <Halide.h>
#include <HalideRuntime.h>
#ifdef APEX
#include "apex_api.hpp"
#endif

#ifdef HPX_INCLUDE
#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>
#include <hpx/runtime.hpp>
#endif

int profile_halide_do_par_for(void *ctx, int (*f)(void *, int, uint8_t *),
                              int min, int extent, uint8_t *closure)
{
#ifdef HPX_INCLUDE
//    std::size_t const os_threads = hpx::get_os_thread_count();
//
//    std::size_t chunk_size = extent/os_threads;
//    std::cout<<min<<","<<extent<<","<<chunk_size<<std::endl;
//
//    hpx::execution::dynamic_chunk_size ds(chunk_size);
    auto annotated_exec = hpx::experimental::prefer(
            hpx::execution::experimental::with_annotation, hpx::execution::par.executor(), "test");
    hpx::for_loop(hpx::execution::par.on(annotated_exec), min, min + extent,
                  [&](int i) {
                      f(ctx, i, closure); });


//    hpx::for_loop(hpx::execution::par.with(ds), min, min + extent,
//                  [&](int i) {
//                      apex::scoped_timer _iter(__func__);
//                      f(ctx, i, closure); });

//    hpx::for_loop(hpx::execution::par, min, min + extent,
//                  [&](int i) {
////                      apex::scoped_timer _iter(__func__);
//                      halide_do_task(ctx, f, i, closure); });
#else
    halide_default_do_par_for(ctx,f,min, extent, closure);
#endif
    return 0;
}
int profile_halide_do_task(void *ctx, halide_task_t f, int idx, uint8_t *closure)
{
#ifdef APEX
    apex::scoped_timer _task(__func__);
#endif
    return halide_default_do_task(ctx,f,idx, closure);
}

int profile_halide_do_loop_task(void *ctx, halide_loop_task_t f,
                           int min, int extent, uint8_t *closure,void *task_parent)
{
#ifdef APEX
    apex::scoped_timer _loop(__func__);
#endif
    return halide_default_do_loop_task(ctx,f,min, extent, closure, task_parent);
}


struct init{
    init(){
        halide_set_custom_do_par_for(&profile_halide_do_par_for);
        halide_set_custom_do_task(&profile_halide_do_task);
        halide_set_custom_do_loop_task(&profile_halide_do_loop_task);
    }
};

init startup;