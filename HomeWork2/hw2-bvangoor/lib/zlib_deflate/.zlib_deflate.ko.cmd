cmd_lib/zlib_deflate/zlib_deflate.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o lib/zlib_deflate/zlib_deflate.ko lib/zlib_deflate/zlib_deflate.o lib/zlib_deflate/zlib_deflate.mod.o
