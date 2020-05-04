# Anotações

Acionar aqui as minhas anotações e avanços no trabalho.

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