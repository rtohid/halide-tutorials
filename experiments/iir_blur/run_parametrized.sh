#!/bin/bash

machine="rostam"
node=`hostname -s`

app="iir_blur_filter"
run_dir="/work/rtohid/harris/halide-tutorials/hpx/apps/iir_blur"
args="rgb.png rgb_filtered.png"

threads=(1 2 4 8 12 16 20 24 28 32 36 40)
# threads=(16)
hpx_dir=/work/rtohid/p3hpc/hpx/
halide_dir=/work/rtohid/p3hpc/Halide/

# run direcroties
halide_run_dir=${run_dir}
hpx_run_dir=${run_dir}/hpx

# log directories
logs_dir=${run_dir}/logs/`date +'%Y_%m_%d--%H-%M-%S'`
halide_logs_dir=${logs_dir}/halide
hpx_logs_dir=${logs_dir}/hpx

mkdir -p ${halide_logs_dir}
mkdir -p ${hpx_logs_dir}

# logging metadata
echo "Date:" >> ${logs_dir}/meta.txt
date >> ${logs_dir}/meta.txt
echo >> ${logs_dir}/meta.txt

echo "Node:" >> ${logs_dir}/meta.txt
hostnamectl >> ${logs_dir}/meta.txt
echo >> ${logs_dir}/meta.txt

echo "HPX:" >> ${logs_dir}/meta.txt
cd ${hpx_dir} && echo `git log --pretty=format:'%H%aD' -n 1` >> ${logs_dir}/meta.txt
cd ${hpx_dir} && git remote -v >> ${logs_dir}/meta.txt
echo >> ${logs_dir}/meta.txt

echo "Halide:" >> ${logs_dir}/meta.txt
cd ${halide_dir} && echo `git log --pretty=format:'%H%aD' -n 1` >> ${logs_dir}/meta.txt
echo >> ${logs_dir}/meta.txt

echo "Application:" >> ${logs_dir}/meta.txt
echo ${halide_run_dir}/${app} >> ${logs_dir}/meta.txt
echo ${hpx_run_dir}/${app} >> ${logs_dir}/meta.txt
cd ${run_dir} && echo `git log --pretty=format:'%H%aD' -n 1` >> ${logs_dir}/meta.txt
echo >> ${logs_dir}/meta.txt

cp ${run_dir}/run_parametrized.sh ${logs_dir}/


# run halide
runtime=halide
cd ${halide_run_dir}
for num_th in ${threads[@]}
do
		HL_NUM_THREADS=${num_th} ${halide_run_dir}/cmake-build-release/${app} ${args} \
			       &>> ${halide_logs_dir}/${machine}--${node}--${runtime}--${app}--${num_th}.log
		# HL_NUM_THREADS=${num_th} perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ${halide_run_dir}/cmake-build-release/${app} ${args} \
		# 	       &>> ${halide_logs_dir}/${machine}--${node}--${runtime}--${app}--${num_th}.log
done

# run hpx
runtime=hpx
cd ${hpx_run_dir}
for num_th in ${threads[@]}
do
		HL_NUM_THREADS=1 OMP_NUM_THREADS=1 ${hpx_run_dir}/cmake-build-release/${app} ${args} \
						   --hpx:threads=${num_th} \
						   &>> ${hpx_logs_dir}/${machine}--${node}--${runtime}--${app}--${num_th}.log
		# HL_NUM_THREADS=1 OMP_NUM_THREADS=1 perf stat -e task-clock,cycles,instructions,cache-references,cache-misses ${hpx_run_dir}/cmake-build-release/${app} ${args} \
		# 				   --hpx:threads=${num_th} \
		# 				   &>> ${hpx_logs_dir}/${machine}--${node}--${runtime}--${app}--${num_th}.log
done
