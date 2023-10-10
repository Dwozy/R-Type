# Protocol for R-Type server/client exchange

### Data stucture:
Data must be sent to server in this format:

|Magic Number|PacketType|Payload Size|
|---|---|---|
|Unsigned integer 32 bytes|Unsigned integer 8 bytes|Unsigned integer 16 bytes|

|Data body|
|---|
|See Below|

### Pascal string:

Pascal string (noted Pstring) are string not null terminated, with the number of character before the string.

|Size of string|String|
|---|---|
|Unsigned integer 16 bytes|string (not null terminated)|

### Event types:
- #### Player related events:
    - #### Move*
      Data represent position and normalised movement vector:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |Unsigned integer 16 bytes|Float|Float|Float|Float|
    - #### Shoot*
      Data represent position and normalised directional vector:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |Unsigned integer 16 bytes|Float|Float|Float|Float|
    - #### Take damage*
      |id|
      |---|
      |Unsigned integer 16 bytes|
      No Additional data
    - #### Die
      |id|
      |---|
      |Unsigned integer 16 bytes|
      No Additional data
    - #### Take bonus*
      Data represent position and bonus type:
      |id|x|y|bonus_id|
      |---|---|---|---|
      |Unsigned integer 16 bytes|Float|Float|Unsigned integer 8 bytes|

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
      |Unsigned integer 16 bytes|Pstring|Unsigned integer 8 bytes|...|
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
      |Unsigned integer 8 bytes|

- #### Enemy related events:
    - #### Spawn
      Data represent position of the enemy and its id:
      |enemy_id|x|y|
      |---|---|---|
      |Unsigned integer 16 bytes|Float|Float|
    - #### Move
      Data represent movement vector:
      |enemy_id|x|y|
      |---|---|---|
      |Unsigned integer 16 bytes|Float|Float|
    - #### Shoot
      Data represent position and normalised directional vector:
      |enemy_id|x|y|dx|dy|
      |---|---|---|---|---|
      |Unsigned integer 16 bytes|Float|Float|Float|Float|
    - #### Take damage*
      Data represent enemy:
      |enemy_id|
      |---|
      |Unsigned integer 16 bytes|
    - #### Die
      Data represent enemy:
      |enemy_id|
      |---|
      |Unsigned integer 16 bytes|
    - #### Drop bonus
      Data represent position of the enemy, its id and the bonus:
      |x|y|enemy_id|bonus_id|
      |---|---|---|---|
      |Float|Float|Unsigned integer 16 bytes|Unsigned integer 8 bytes|

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
