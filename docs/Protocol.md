# Protocol for R-Type server/client exchange

### Data stucture:
Data must be sent to server in this format:

|Magic Number|PacketType|Payload Size|
|---|---|---|
|32-bit unsigned integer|8-bit unsigned integer|16-bit unsigned integer|

|Data body|
|---|
|See Below|

### Pascal string:

Pascal string (noted Pstring) are string not null terminated, with the number of character before the string.

|Size of string|String|
|---|---|
|16-bit unsigned integer|string (not null terminated)|

### Event types:
- #### Player related events:
    - #### Move*
      Data represent position and normalised movement vector:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |16-bit unsigned integer|Float|Float|Float|Float|
    - #### Shoot*
      Data represent position and normalised directional vector:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |16-bit unsigned integer|Float|Float|Float|Float|
    - #### Take damage*
      |id|
      |---|
      |16-bit unsigned integer|
      No Additional data
    - #### Die
      |id|
      |---|
      |16-bit unsigned integer|
      No Additional data
    - #### Take bonus*
      Data represent position and bonus type:
      |id|x|y|bonus_id|
      |---|---|---|---|
      |16-bit unsigned integer|Float|Float|8-bit unsigned integer|

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
      |16-bit unsigned integer|Pstring|8-bit unsigned integer|...|
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
      |8-bit unsigned integer|

- #### Enemy related events:
    - #### Spawn
      Data represent position of the enemy and its id:
      |enemy_id|x|y|
      |---|---|---|
      |16-bit unsigned integer|Float|Float|
    - #### Move
      Data represent movement vector:
      |enemy_id|x|y|
      |---|---|---|
      |16-bit unsigned integer|Float|Float|
    - #### Shoot
      Data represent position and normalised directional vector:
      |enemy_id|x|y|dx|dy|
      |---|---|---|---|---|
      |16-bit unsigned integer|Float|Float|Float|Float|
    - #### Take damage*
      Data represent enemy:
      |enemy_id|
      |---|
      |16-bit unsigned integer|
    - #### Die
      Data represent enemy:
      |enemy_id|
      |---|
      |16-bit unsigned integer|
    - #### Drop bonus
      Data represent position of the enemy, its id and the bonus:
      |x|y|enemy_id|bonus_id|
      |---|---|---|---|
      |Float|Float|16-bit unsigned integer|8-bit unsigned integer|

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
