cmd_drivers/net/ethernet/mellanox/mlx4/mlx4_en.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/ethernet/mellanox/mlx4/mlx4_en.ko drivers/net/ethernet/mellanox/mlx4/mlx4_en.o drivers/net/ethernet/mellanox/mlx4/mlx4_en.mod.o