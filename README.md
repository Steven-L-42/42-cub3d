# Cub3D - Wolfenstein3D

![cub3d](https://github.com/ayogun/42-project-badges/blob/main/badges/cub3dm.png?raw=true)

# version (2024.01.09) - Torch and Random Map Generator

https://github.com/Steven-L-42/42-cub3d/assets/102829233/96bb6419-d8fc-4945-8098-eba0144b7bd9

# version (2024.01.08)

https://github.com/Steven-L-42/42-cub3d/assets/102829233/9a9279c5-079c-46e1-9933-b8b9a18b1933

# version (2024.01.07)

https://github.com/Steven-L-42/42-cub3d/assets/102829233/6c908f4d-8fc4-47f7-b6bd-5786e662b7b0


# version (2024.01.03)

https://github.com/Steven-L-42/42-cub3d/assets/102829233/4bd74288-0d50-47f0-9cae-4ee1aaacfded


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

