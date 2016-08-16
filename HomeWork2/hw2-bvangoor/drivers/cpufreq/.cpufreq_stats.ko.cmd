cmd_drivers/cpufreq/cpufreq_stats.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/cpufreq/cpufreq_stats.ko drivers/cpufreq/cpufreq_stats.o drivers/cpufreq/cpufreq_stats.mod.o
