# armageddon_joint_states

| Comando | Nome              | Ação                                                         |
| ------- | ----------------- | ------------------------------------------------------------ |
| SK      | Stop & Kill       | Interrupção do motor                                         |
| DI      | Distance/Position | Define um número de passos                                   |
| FL      | Feed to Length    | 200000 - Executa o número de passos                          |
| AL      | Alarm Code        | 0002 - CCW Limit<br/>0004 - CW Limit                         |
| CM      | Command Mode      | 1 - Commanded Torque<br />7 - Step & Direction<br />21 - Point-to-Point |
| DL      | Define Limits     | 1 - nothing limits are normally open<br />3 - nothing limits are not used<br />Obs: Para os sensores de limite físico funcionarem o modo CM não pode estar em  7 ou  11-18 |

### Comandos iniciais 

```serial
HR
SK
MV
RLs
EG
IF
PR
PR5
PM
RV
SR-1
SV
SR100
SV
```

