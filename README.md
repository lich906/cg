## Computer graphics course
[Original Course Tasks](https://github.com/alexey-malov/cg-course)

It's adviced to clone this repository including all submodules:
```shell
git clone --recurse-submodules https://github.com/lich906/cg.git
```

Use [vcpkg](https://github.com/microsoft/vcpkg.git) for building up external libraries and Visual Studio to build project.
Each solution has it's own `vcpkg.json` used by vcpkg manifest mode.
In each solution you can find `README.md` file explaining how to set up libraries properly.

Build is tested only with:
* vcpkg version `2022-11-10-5fdee72bc1fceca198fb1ab7589837206a8b81ba`
* Visual Studio 2022
* latest external libraries versions at the time of project creation

If some project isn't build correctly and you are confident it's not your mistake, well... Fix it! (and make PR if possible :) )
