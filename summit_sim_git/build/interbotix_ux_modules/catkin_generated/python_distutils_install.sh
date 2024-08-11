#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_toolboxes/interbotix_ux_toolbox/interbotix_ux_modules"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/bryan/dissertation/Dissertation-/summit_sim_git/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/bryan/dissertation/Dissertation-/summit_sim_git/install/lib/python3/dist-packages:/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_ux_modules/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_ux_modules" \
    "/usr/bin/python3" \
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_toolboxes/interbotix_ux_toolbox/interbotix_ux_modules/setup.py" \
     \
    build --build-base "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_ux_modules" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/bryan/dissertation/Dissertation-/summit_sim_git/install" --install-scripts="/home/bryan/dissertation/Dissertation-/summit_sim_git/install/bin"
