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

### Event types:
- #### Player related events:
    - #### Move*
      Data represent normalised movement vector:
      |x|y|dx|dy|
      |---|---|---|---|
      |Int32|Int32|Int8|Int8|
    - #### Shoot*
      Data represent position and normalised directional vector:
      |x|y|dx|dy|
      |---|---|---|---|
      |Int32|Int32|Int8|Int8|
    - #### Take damage*
      No Additional data
    - #### Die
      No Additional data
    - #### Take bonus*
      Data represent position and bonus type:
      |x|y|bonus_id|
      |---|---|---|
      |Int32|Int32|Uint8|

- #### Room related events:
    - #### Create room**
      Data represent room:
      |room_name|
      |---|
      |string|
    - #### Get rooms
      Data represent list of available room:
      |number of rooms|room_name|players in room|...|
      |---|---|---|---|
      |Uint16|string|Uint8|...|
    - #### Join*
      Data represent room:
      |room_name|
      |---|
      |string|
    - #### Leave*
      No Additional data

- #### Enemy related events:
    - #### Spawn
      Data represent position of the enemy and its id:
      |x|y|enemy_id|
      |---|---|---|
      |Int32|Int32|Uint16|
    - #### Move
      Data represent movement vector:
      |x|y|
      |---|---|
      |Int8|Int8|
    - #### Shoot
      Data represent position and normalised directional vector:
      |x|y|dx|dy|
      |---|---|---|---|
      |Int32|Int32|Int8|Int8|
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
      |Int32|Int32|Uint16|Uint8|

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
      No Additional data

*: sent by client, redistributed by server in the corresponding room with the id of the sender
**: sent by client, but not redistributed
