#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	int	new_fd;
	int original_fd;

	original_fd = dup(STDOUT_FILENO);

	new_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(new_fd, STDOUT_FILENO);
	write(STDOUT_FILENO, "new_fd\n", 7);
	close(new_fd);

	dup2(original_fd, STDOUT_FILENO);
	write(STDOUT_FILENO, "origin_fd\n", 10);
	close(original_fd);
	return 0;
}
