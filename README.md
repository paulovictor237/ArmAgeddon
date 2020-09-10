# ArmAgeddon

Este trabalho foi desenvolvido com a versão recomendada (2020) ROS1 Melodic Morenia para a distribuição Linux Ubuntu Budgie 18.04 LTS, e compilado com a extensão catkin-tools (catkin build). Vale o registro que a última versão do ROS1 será a Noetic Ninjemys, mas no momento se encontra em fase Beta. Existe também o projeto Moveit 2 para o ROS2, porém ainda está em processo de migração.

<img src="documentos/imagens/planning.png"/>

# A. Requisitos de software

1. Ubuntu Budgie 18.04 LTS
2. ROS Melodic Morenia
3. MoveIt

# B. Instalação

Em um outro repertório de minha autoria você pode encontrar um bash-script para instalar o Moveit em um Ubuntu 18.04 LTS.

Siga os passos descritos em: [BashScript-RosMoveit](https://github.com/paulovictor237/BashScript-RosMoveit)

# C. Aplicações

Aqui se encontra a descrição das 5 aplicações implementadas.

**1. GoRandom**

O objetivo dessa aplicação é criar um código curto e simples que apenas executa um movimento randômico. Como normalmente o ponto está muito distante da atual posição do robô, isto origina dois problemas, o tempo padrão para o MoveIt calcular a trajetória é insuficiente e o caminho é imprevisível. Para melhorar a frequência com que esse programa encontra uma trajetória de sucesso, o tempo padrão de 5 segundos foi aumentado para 10, e o algoritmo de planejamento de trajetória foi forçado para executar com o RRT, para garantir que uma trajetória seja encontrada, mesmo não sendo a ideal.

**2. GoHome**

A aplicação GoHome força todas as juntas do robô para o valor zero, independente de onde ele esteja. Este código também serve como uma demonstração dos tipos de mensagens que o ROS pode emitir, e imprime na tela várias informações do robô extraídas dos próprios métodos da classe MoveGroupInterface.

**3. GoTypeMoves**

TypeMoves é uma demonstração dos métodos de movimento que o MoveGroupInterface dispõe. A aplicação executa as seguintes tarefas.

+ Planejar e executar trajetória para um ponto qualquer;
+ Planejar e executar trajetória inserindo valores na juntas;
+ Planejar e executar trajetória lineares em um Plano Cartesiano

Nesta prática foi necessário converter a orientação *Roll Pitch Yall* em Quaternions antes de atribuir os valores ao robô.

O código também faz uso da classe "MoveItVisualTools" para apresentar mensagens e desenhar trajetórias no Rviz.

**4. CartesianReader**

A aplicação CartesianReader lê o arquivo [positions.md](armageddon_robot/arquivos/positions.md) executa a chamada da função **computeCartesianPath**. Os parâmetros dessa função são descritos no arquivo [CartesianReader.md](documentos/CartesianReader.md).

**5. StopMove**

Esta aplicação para qualquer movimento em que o robo esteja operando. Após executar esta aplicação é necessário publicar a palavra 'STOP' no Tópico `/armageddon/stop_robot` em um terminal separado.

```
rostopic pub -1 /armageddon/stop_robot std_msgs/String "data: 'STOP'" 
```

# D. Execução

Abra dois terminais e execute os seguintes códigos. Você pode descomentar o `use_gui:=true` caso queira controlar os motores com uma interface gráfica.

> Terminal 1

```bash
roslaunch armageddon_moveit demo.launch #use_gui:=true
```

No segundo terminal rode uma das aplicações abaixo:

> Terminal 2

```bash
rosrun armageddon_robot GoRandom
rosrun armageddon_robot GoHome
rosrun armageddon_robot GoTypeMoves
rosrun armageddon_robot CartesianReader
rosrun armageddon_robot StopMove
```

License
----

Copyright (C) 2020 Paulo Victor , All rights reserved.

**Free Software, Hell Yeah!**
