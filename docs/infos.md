
### Allowed Functions:
open, close, 				(files)
malloc, free				(memory)
read, write, printf,		(text)
strerror, perror, exit		(error hadeling)
all math library			(flouts/doubles)
MinilibX library -> MLX42	(42 Graphics library)
gettimeofday				(time)


# Design decision:

t_norm_ray (normal rays) ray out of a hit points outsiet the opject not insed other than the book is working with! beacous i want to lean and thaink and at the moment its easyer to decied on the coloring and i dont need to change the new t_norm_ray struct.


# function naming
is_ -> return bool for if/else statments
get_ -> return a (new/or pointer) obj/data

_vec3 -> type at the end

x_to_y -> convert x to y


# Execution flow:

init data
init mlx
parse file
init scene
render the image -> diplay


keyboard change:
change whats needed in the strucks and call render again


on error: print error massage then close

close:
termainte mlx (cleans itself)
free all




[raytraccer book](https://raytracing.github.io/books/RayTracingInOneWeekend.html#addingasphere/creatingourfirstraytracedimage)





https://github.com/RayTracing/raytracing.github.io/
https://graphicscodex.com/app/app.html?page=_rn_rayCst