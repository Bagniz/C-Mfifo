.SILENT:
all:
	cd config && make
	cd tests/mfifo_capacity && make
	cd tests/mfifo_connect && make
	cd tests/mfifo_disconnect && make
	cd tests/mfifo_free_memory && make
	cd tests/mfifo_lock_unlock && make
	cd tests/mfifo_read_write && make
	cd tests/mfifo_trylock_unlock && make
	cd tests/mfifo_trywrite_read && make
	cd tests/mfifo_unlink && make
	cd tests/mfifo_write_partial_read && make

clean:
	cd config && make clean
	cd tests/mfifo_capacity && make clean
	cd tests/mfifo_connect && make clean
	cd tests/mfifo_disconnect && make clean
	cd tests/mfifo_free_memory && make clean
	cd tests/mfifo_lock_unlock && make clean
	cd tests/mfifo_read_write && make clean
	cd tests/mfifo_trylock_unlock && make clean
	cd tests/mfifo_trywrite_read && make clean
	cd tests/mfifo_unlink && make clean
	cd tests/mfifo_write_partial_read && make clean