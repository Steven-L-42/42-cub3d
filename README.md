# Cub3D - Wolfenstein3D

![cub3d](https://github.com/ayogun/42-project-badges/blob/main/badges/cub3dm.png?raw=true)

```c
#include <stdio.h>

int	show_contributor(const char* name, const char* github)
{
	if (!printf("👨‍💻 Contributor: %s | GitHub: %s\n", name, github))
		return (write(2, "Error!\n" 7), 1);
	return (0);
}

int	main(void)
{
	if (show_contributor("Jan", "https://github.com/Jano844"))
		return (1);
	if (show_contributor("Steven", "https://github.com/Steven-L-42"))
		return (1);
	return (0);
}

// expected output:
// 👨‍💻 Contributor: Jan | GitHub: https://github.com/Jano844
// 👨‍💻 Contributor: Steven | GitHub: https://github.com/Steven-L-42
```
