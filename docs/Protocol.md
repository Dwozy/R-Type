# Protocol for R-Type server/client exchange

### Data stucture:
WIP

### Event types:
- #### Player related events:
    - Move*
    - Shoot*
    - Take damage*
    - Die
    - Take bonus*
    - Join*
    - Leave*

- #### Enemy related events:
    - Spawn
    - Move
    - Shoot
    - Take damage*
    - Die
    - Drop bonus

- #### Stage related events:
    - Start
    - Win
    - Game Over

*: sent by client, redistributed by server
