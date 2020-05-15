# Anotações

[TOC]

# [!] Invalid Trajectory

Em caso de aparecer o seguinte erro ao tentar executar um *goal to*

> **Invalid Trajectory: start point deviates from current robot state more than …**


Adicione as linhas abaixo no FINAL do arquivo /launch/move_group.launch

```html
<!-- default 0.01, disable 0.0 -->
<param name="/move_group/trajectory_execution/allowed_start_tolerance" value="0.0"/>
```

Se não resolver adicione também as linhas a baixo.

```html
<param name = "/move_group/trajectory_execution/allowed_execution_duration_scaling" value="4.0" />
<param name = "/move_group/trajectory_execution/execution_duration_monitoring" value="false" />
```

E cerfique-se que o Planing Scene Topic está em "/move_group/monitored_planning_scene"

https://github.com/jacknlliu/development-issues/issues/67
https://ms-iot.github.io/ROSOnWindows/Moveit/UR3.html
https://moveit.ros.org/moveit!/ros/2017/01/03/firstIndigoRelease.html

# URDF caminho relativo

Como fazer [Macros](http://wiki.ros.org/urdf/Tutorials/Using%20Xacro%20to%20Clean%20Up%20a%20URDF%20File)

```html
<xacro:property name="description_pkg" value='franka_description' />
<xacro:property name="meshfile1" value="package://franka_description/meshes/visual" />
<xacro:property name="meshfile2" value="file://../franka_description/meshes/visual" />
<xacro:property name="meshscale" value="0.6" />
    
<geometry>
<mesh filename="package://${description_pkg}/meshes/visual/link0.dae"/>
<mesh filename="${meshfile1}/link0.dae" scale="${meshscale}"/>
<mesh filename="${meshfile2}/link0.dae" scale="${meshscale}"/>
</geometry>
```

https://answers.ros.org/question/263308/is-it-possible-to-use-relative-path-for-mesh-filename-in-urdf/
https://answers.ros.org/question/38956/pass-parameters-to-xacro-in-launch-file/
https://www.theconstructsim.com/ros-projects-my-robotic-manipulator-6-stl-mesh-file-for-urdf-link/