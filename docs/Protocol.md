# Protocol for R-Type server/client exchange

### Data stucture:
Data must be sent to server in this format:

|Size of data|Type of Event|Additional data|
|---|---|---|
|Uint16|Uint16|{...}|

Data will be received in the client in this format:

|Size of data|Original Sender Id|Type of Event|Additional data|
|---|---|---|---|
|Uint16|Uint16 (0 if sent directly by the server)|Uint16|{...}||

### Pascal string:

Pascal string (noted Pstring) are string not null terminated, with the number of character before the string.

|Size of string|String|
|---|---|
|Uint16|string (not null terminated)|

### Event types:
- #### Player related events:
    - #### Move*
      Data represent position and normalised movement vector:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |Uint16|Float|Float|Float|Float|
    - #### Shoot*
      Data represent position and normalised directional vector:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |Uint16|Float|Float|Float|Float|
    - #### Take damage*
      [id|
      |---|
      Uint16
      No Additional data
    - #### Die
      |id|
      |---|
      Uint16
      No Additional data
    - #### Take bonus*
      Data represent position and bonus type:
      |id|x|y|bonus_id|
      |---|---|---|---|
      |Uint16|Float|Float|Uint8|

- #### Room related events:
    - #### Create room**
      Data represent room:
      |room_name|
      |---|
      |Pstring|
    - #### Get rooms
      Data represent list of available room:
      |number of rooms|room_name|players in room|...|
      |---|---|---|---|
      |Uint16|Pstring|Uint8|...|
    - #### Join*
      Data represent room:
      |room_name|
      |---|
      |Pstring|
    - #### Leave*
      No Additional data
    - #### Choice stage*
      Data represent stage chosen:
      |stage_number|
      |---|
      |Uint8|

- #### Enemy related events:
    - #### Spawn
      Data represent position of the enemy and its id:
      |x|y|enemy_id|
      |---|---|---|
      |Float|Float|Uint16|
    - #### Move
      Data represent movement vector:
      |x|y|
      |---|---|
      |Float|Float|
    - #### Shoot
      Data represent position and normalised directional vector:
      |x|y|dx|dy|
      |---|---|---|---|
      |Float|Float|Float|Float|
    - #### Take damage*
      Data represent enemy:
      |enemy_id|
      |---|
      |Uint16|
    - #### Die
      Data represent enemy:
      |enemy_id|
      |---|
      |Uint16|
    - #### Drop bonus
      Data represent position of the enemy, its id and the bonus:
      |x|y|enemy_id|bonus_id|
      |---|---|---|---|
      |Float|Float|Uint16|Uint8|

- #### Stage related events:
    - #### Start
      No Additional data
    - #### Win
      No Additional data
    - #### Game Over
      No Additional data

- #### Response events (server response to the original sender):
    - #### OK
      No Additional data
    - #### KO
      Data is the error message:
      |message|
      |---|
      |Pstring|

*: sent by client, redistributed by server in the corresponding room with the id of the sender

**: sent by client, but not redistributed
