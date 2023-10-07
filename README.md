# Distributed systems algorithims
## Clock Sync Algorithms

### Physical Clocks
- Physical clocks are hardware-based timekeeping devices.
- They provide real-time measurements based on oscillators or crystal oscillators.
- Physical clocks may not be perfectly synchronized due to clock drift, causing time inconsistencies in distributed systems.

#### 1. Network Time Protocol
- **Overview**: NTP is a widely-used protocol for clock synchronization in distributed systems.
- **Function**: It adjusts clock values to account for network delays and clock drifts.
- **Use Cases**: NTP is suitable for general-purpose clock synchronization where high precision is not required.
- **Implementation**: NTP involves a hierarchical structure of time servers and clients to achieve synchronization.
![ntp](https://i.imgur.com/HfKPnZzm.png)

#### 2. Christian's Clock
- **Overview**: Christian's algorithm is a simple clock synchronization algorithm.
- **Function**: It calculates the offset between a client's clock and a time server's clock, assuming symmetric network delays.
- **Use Cases**: Christian's algorithm is suitable for basic clock synchronization in distributed systems.
![cristan](https://i.imgur.com/3bURIU7.png)

#### 3. Berkeley Clock
- **Overview**: The Berkeley algorithm is used for clock synchronization in loosely coupled distributed systems.
- **Function**: It employs a master-slave architecture, where a master node collects time information from slave nodes and adjusts their clocks.
- **Use Cases**: Berkeley algorithm is appropriate when a centralized approach is acceptable.
![berkeley](https://i.imgur.com/dtmwkMz.png)

### Logical Clocks
- Logical clocks are logical constructs used to order events in a distributed system.
- They do not rely on physical time but provide a logical order for events.
- Logical clocks help in establishing causal relationships and ensuring event consistency in distributed systems.

#### 1. Lamport Clock
- **Overview**: Lamport clocks are logical clocks introduced by Leslie Lamport.
- **Function**: They provide a partial ordering of events in a distributed system, based on causality.
- **Use Cases**: Lamport clocks are useful for reasoning about event ordering and causal relationships in distributed systems.
![lamport](https://i.imgur.com/C9P45yS.png)

#### 2. Vector Clock
- **Overview**: Vector clocks extend Lamport clocks for more complex event ordering.
- **Function**: They maintain a vector of clocks, one per process, to capture dependencies between events.
- **Use Cases**: Vector clocks are suitable for applications where understanding concurrent events and their relationships is crucial.
![vector](https://i.imgur.com/l2h7BNm.png)

## Implementation
