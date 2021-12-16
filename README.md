# CPP_In_Order_Packet_Delivery

## 1. Overview
your ae receivind and array of packet ID and based on the sequence of reception and the window size you should decide which to receive and which to drop and return them in 2 separate arrays  

## 2. Queue 
![image](https://user-images.githubusercontent.com/68570192/146443148-78dc7dbc-b1ea-4045-b043-555faf085272.png)

## 2. Data representation 

Received packet IDs: represented as array of integer 
Waiting List: represented as in order static queue 

•	Waiting List [1]: Stores waiting packets between expected and maximum packet ID

•	Waiting List [2]: Stores waiting packets between zero and end of window size 

Dropped packets IDs: represented as array of integer 


## 3. Main Flow 
![image](https://user-images.githubusercontent.com/68570192/146442852-e39f1e21-8f50-44a8-83cc-e5c3710b328a.png)


