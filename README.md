# ArmAgeddon

Este trabalho foi desenvolvido com a versão recomendada (2020) ROS1 Melodic Morenia para a distribuição Linux Ubuntu Budgie 18.04 LTS, e compilado com a extensão catkin-tools (catkin build). Vale o registro que a última versão do ROS1 será a Noetic Ninjemys, mas no momento se encontra em fase Beta. Existe também o projeto Moveit 2 para o ROS2, porém ainda está em processo de migração.

<img src="/home/paulovictor237/ws_moveit/src/armageddon/documentos/imagens/planning.png" style="zoom: 33%;" />

# A. Software prerequisites

1. Ubuntu Budgie 18.04 LTS
2. ROS Melodic Morenia
3. MoveIt

# B. Installation

Em um outro repertório de minha autoria você pode encontrar um bash-script para instalar o Moveit em um Ubuntu 18.04 LTS.

Siga os passos descritos em: [BashScript-RosMoveit](https://github.com/paulovictor237/BashScript-RosMoveit)

# C. Applications

Aqui se encontra a descrição das 5 aplicações implementadas.

**1. GoRandom**

Vai para uma posição randomica, nem sempre o caminho será possível. Todavia, é enviado uma mensagem sinalizando quando um erro ocorrer.

**2. GoHome**

Escreve em todas as juntas o valor `ZERO`.

**3. GoTypeMoves**

Ilustra as várias formas de se descrever um movimento em c++.

**4. CartesianReader**

A aplicação CartesianReader lê o arquivo [positions.md](armageddon_robot/arquivos/positions.md) executa a chamada da função **computeCartesianPath**. Os parâmetros dessa função são descritos no arquivo [CartesianReader.md](documentos/CartesianReader.md).

**5. StopMove**

Esta aplicação para qualquer movimento em que o robo esteja operando. Após executar esta aplicação é necessário publicar a palavra 'STOP' no Tópico `/armageddon/stop_robot` em um terminal separado.

```
rostopic pub -1 /armageddon/stop_robot std_msgs/String "data: 'STOP'" 
```

# D. Execution

Abra dois terminais e rode os seguintes códigos. Você pode descomentar o `use_gui:=true` caso queira controlar os motores com uma interface gráfica.

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