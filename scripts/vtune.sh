#!/bin/bash

module load vtune

VTUNE_DIR=$WORK/halideData/vtune_dir

mkdir -p $VTUNE_DIR

# IIR Blur
HL_NUM_THREADS=40 vtune --collect hotspots -result-dir $VTUNE_DIR/40_halide_iir_blur \
    $WORK/halide-tutorials/cmake-build/Release/apps/iir_blur/iir_blur_filter_halide \
    $WORK/halide-tutorials/apps/images/rgb.png result_halide.png
HL_NUM_THREADS=16 vtune --collect hotspots -result-dir $VTUNE_DIR/16_halide_iir_blur \
    $WORK/halide-tutorials/cmake-build/Release/apps/iir_blur/iir_blur_filter_halide \
    $WORK/halide-tutorials/apps/images/rgb.png result_halide.png
HL_NUM_THREADS=8 vtune --collect hotspots -result-dir $VTUNE_DIR/8_halide_iir_blur \
    $WORK/halide-tutorials/cmake-build/Release/apps/iir_blur/iir_blur_filter_halide \
    $WORK/halide-tutorials/apps/images/rgb.png result_halide.png
vtune --collect hotspots -result-dir $VTUNE_DIR/40_hpx_iir_blur \
    $WORK/halide-tutorials/cmake-build/Release/apps/iir_blur/iir_blur_filter_hpx \
    $WORK/halide-tutorials/apps/images/rgb.png result_hpx.png --hpx:threads=40 
vtune --collect hotspots -result-dir $VTUNE_DIR/16_hpx_iir_blur 
    $WORK/halide-tutorials/cmake-build/Release/apps/iir_blur/iir_blur_filter_hpx \
    $WORK/halide-tutorials/apps/images/rgb.png result_hpx.png --hpx:threads=16
vtune --collect hotspots -result-dir $VTUNE_DIR/8_hpx_iir_blur \
    $WORK/halide-tutorials/cmake-build/Release/apps/iir_blur/iir_blur_filter_hpx \
    $WORK/halide-tutorials/apps/images/rgb.png result_hpx.pn --hpx:threads=8g

# NL-Means
HL_NUM_THREADS=40 vtune --collect hotspots -result-dir $VTUNE_DIR/40_halide_nl_means \
    $WORK/halide-tutorials/cmake-build/Release/apps/nl_means/nl_means_process_halide \
    7 7 0.12 10 $WORK/halide-tutorials/apps/images/rgb.png
HL_NUM_THREADS=16 vtune --collect hotspots -result-dir $VTUNE_DIR/16_halide_nl_means \
    $WORK/halide-tutorials/cmake-build/Release/apps/nl_means/nl_means_process_halide \
    7 7 0.12 10 $WORK/halide-tutorials/apps/images/rgb.png
HL_NUM_THREADS=8 vtune --collect hotspots -result-dir $VTUNE_DIR/8_halide_nl_means \
    $WORK/halide-tutorials/cmake-build/Release/apps/nl_means/nl_means_process_halide \
    7 7 0.12 10 $WORK/halide-tutorials/apps/images/rgb.png
vtune --collect hotspots -result-dir $VTUNE_DIR/40_hpx_nl_means \
    $WORK/halide-tutorials/cmake-build/Release/apps/nl_means/nl_means_process_hpx \
    7 7 0.12 10 $WORK/halide-tutorials/apps/images/rgb.png --hpx:threads=40
vtune --collect hotspots -result-dir $VTUNE_DIR/16_hpx_nl_means \
    $WORK/halide-tutorials/cmake-build/Release/apps/nl_means/nl_means_process_hpx \
    7 7 0.12 10 $WORK/halide-tutorials/apps/images/rgb.png --hpx:threads=16
vtune --collect hotspots -result-dir $VTUNE_DIR/8_hpx_nl_means \
    $WORK/halide-tutorials/cmake-build/Release/apps/nl_means/nl_means_process_hpx \
    7 7 0.12 10 $WORK/halide-tutorials/apps/images/rgb.png --hpx:threads=8

# Conv Layer
HL_NUM_THREADS=40 vtune --collect hotspots -result-dir $VTUNE_DIR/40_halide_conv_layer \
    $WORK/halide-tutorials/cmake-build/Release/apps/conv_layer/conv_layer_process_halide 
HL_NUM_THREADS=16 vtune --collect hotspots -result-dir $VTUNE_DIR/16_halide_conv_layer \
    $WORK/halide-tutorials/cmake-build/Release/apps/conv_layer/conv_layer_process_halide 
HL_NUM_THREADS=8 vtune --collect hotspots -result-dir $VTUNE_DIR/8_halide_conv_layer \
    $WORK/halide-tutorials/cmake-build/Release/apps/conv_layer/conv_layer_process_halide 
vtune --collect hotspots  -result-dir$VTUNE_DIR/40_hpx_conv_layer \
    $WORK/halide-tutorials/cmake-build/Release/apps/conv_layer/conv_layer_process_hpx --hpx:threads=40
vtune --collect hotspots -result-dir $VTUNE_DIR/16_hpx_conv_layer \
    $WORK/halide-tutorials/cmake-build/Release/apps/conv_layer/conv_layer_process_hpx --hpx:threads=16
vtune --collect hotspots -result-dir $VTUNE_DIR/8_hpx_conv_layer \
    $WORK/halide-tutorials/cmake-build/Release/apps/conv_layer/conv_layer_process_hpx --hpx:threads=8

# Double
HL_NUM_THREADS=40 vtune --collect hotspots -result-dir $VTUNE_DIR/40_halide_doubling \
    $WORK/halide-tutorials/cmake-build/Release/performance/doubling_halide
HL_NUM_THREADS=16 vtune --collect hotspots -result-dir $VTUNE_DIR/16_halide_doubling \
    $WORK/halide-tutorials/cmake-build/Release/performance/doubling_halide
HL_NUM_THREADS=8 vtune --collect hotspots -result-dir $VTUNE_DIR/8_halide_doubling \
    $WORK/halide-tutorials/cmake-build/Release/performance/doubling_halide
vtune --collect hotspots -result-dir $VTUNE_DIR/40_hpx_doubling \
    $WORK/halide-tutorials/cmake-build/Release/performance/doubling_hpx --hpx:threads=40
vtune --collect hotspots -result-dir $VTUNE_DIR/16_hpx_doubling \
    $WORK/halide-tutorials/cmake-build/Release/performance/doubling_hpx --hpx:threads=16
vtune --collect hotspots -result-dir $WORK/halide/vtune_dir/8_hpx_doubling \
    $WORK/halide-tutorials/cmake-build/Release/performance/doubling_hpx  --hpx:threads=8

