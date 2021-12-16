# CPP_In_Order_Packet_Delivery

## 1. Overview
Received packet IDs: represented as array of integer 
Waiting List: represented as in order static queue 
•	Waiting List [1]: Stores waiting packets between expected and maximum packet ID
•	Waiting List [2]: Stores waiting packets between zero and end of window size 
Dropped packets IDs: represented as array of integer 

## 2. Queue 
![image](https://user-images.githubusercontent.com/68570192/146443148-78dc7dbc-b1ea-4045-b043-555faf085272.png)

## 3. Main Flow 
![image](https://user-images.githubusercontent.com/68570192/146442852-e39f1e21-8f50-44a8-83cc-e5c3710b328a.png)

## 4.	Code Snippets  
'''int R_Backets[1000];				// array for the received packet IDs
st_queue<int> OOO_Backets[2];		// define 2 queues to represent the waiting list
// at any time one of them stores OOO Packets between [expected and maximum]
// the other will stores OOO Packets starts from (0)
int* D_Backets=new int[argn];		// array for the dropped data

'''
