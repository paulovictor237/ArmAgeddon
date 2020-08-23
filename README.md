# Configurações
## Velocity & Acceleration
Velocidade e Aceleração máxima
Para realizar caminhos cartesianos é recomendado usar 5% (0.05)
O valor padrão é 10% (0.10)
Defina seu valor padrão no arquivo joint_limits.yaml 

```c++
group.setMaxVelocityScalingFactor(0.05); 
group.setMaxAccelerationScalingFactor(0.05);
```
## Planning Time

O planejamento com restrições pode ser lento porque cada amostra deve chamar um solucionador de cinemática inversa. 
O valor padrão é 5 segundos 
É comum aumentar esse tempo quando se está calculando uma trajetória de multiplos pontos
Para garantir que o planejador tenha tempo suficiente para ter sucesso aumente para 10s

```c++
group.setPlanningTime(10.0);
```
## End Effector Step

eef_step tamanho de passo máximo em metros entre o efetor final e os pontos da trajetória

```c++
  const double eef_step = 0.01;
```
## Jump Threshold

Jump_threshold  - desativa-lo pode evitar pulos no calculo da cinematica inversa

```c++
  const double jump_threshold = 0.0;
```
## Avoid Collisions

avoid_collisions - colisões são evitadas se for definido como true.
Entretanto, se as colisões não podem ser evitadas, a função falha. 

```c++
  bool avoid_collisions=true;
```