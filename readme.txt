 ONLINE TICKET RESERVATION SYSTEM
1.Compile the server program ====> gcc ticket.c -o ticket -lpthread
2.Compile the client program ====> gcc client1.c -o client
3.Run the server executable file ====> ./ticket
4.Can handle upto 50 clients
5.Run the client executable file ====> ./client

6.The main menu is 

ONLINE TICKET RESERVATION SYSTEM 


	MAIN MENU


	01.Normal Account


	02.Agent Account


	03.Administrative Account


	 Select your account (1-3)


7.Select options by giving number from 1 to 3

8.Normal Account 

  8.1 Give the answer of having an account or not by giving "Yes" or "No"

    	Do you have existing account ?

	 Give Yes or No 

  8.2 Then login to your account

     	Please login into your account

	 Enter your name : 
       
         Enter your password : 
  


   8.3 Normal account menu
       
      	WELCOME TO RAILWAY PORTAL


	Available facalities are


	01.Book Ticket


	02.View Previous Bookings


	03.Update Booking


	04.Cancel Booking


	Select from (1-4)

   8.3.1 Book Ticket
         Select the train ===> Train A, Train B,Train C
         Select the class ===> First AC,Second AC,Sleeper
         Booking done

   8.3.2 View Previous Bookings
         Ticket No. Train No.   Class            Booking Time
       14       A       1AC       Sun Oct 24 15:16:26 2021
       16       C       2AC       Sun Oct 24 15:17:13 2021
       17       C       1AC       Sun Oct 24 15:17:26 2021
       19       C       1AC       Sun Oct 24 17:11:06 2021
       14       B       SL        Sun Oct 24 17:14:56 2021
       16       A       1AC       Mon Oct 25 00:46:27 2021
       17       A       2AC       Mon Oct 25 00:46:27 2021
       18       A       1AC       Thu Oct 28 20:21:09 2021
   
   8.3.3  Update Booking
        1.We have to give the details of the ticket no. and train no. to update the ticket
          Give the ticket details to update --- Ticket no. and train no. (Press enter after giving ticket no. to give train no.)
           14
           A
 
        2.We have to enter the class we want to change .
          1 for 1AC , 2 for 2AC, 3 for SL
         
        3.Update done  


   8.3.4 Cancel Booking
        1.We have to give the details of the ticket no. and train no. to cancel the ticket
        2.Booking canceled
 


 9. Agent Account  

     9.1 Give the answer of having an account or not by giving "Yes" or "No"

        Do you have existing account ?

         Give Yes or No

    9.2 Then login to your account

        Please login into your account

         Enter your name :

         Enter your password :


    9.3 Name of the client for which you will do operations
  
               	Name of the client
        

    9.4 Choose options
        
       	Available options are 


	01.Book Ticket


	02.View Tickets

   
 10.Administrative Account
    
  10.1  There is only one admin for this platform.
        The account name is ===>admin.
        The admin pass is   ===>123adm.

  10.2 On login we will get all account list
      
         	ADMIN ACCOUNT
   List of the accounts present
   Account name   Password 
   abc             3456
   ert             345
   uio             987
   qwe             456

  
  10.3 Give the name of account for which operations will be performed

       	Name of the account for applying operations 
  
  10.4 Operation available are

     	Available operations are 


	01.View all


	02.View


	03.Book ticket


	04.Modify


	05.Cancel booking
 
 10.5 Give number 1 to 5 for a specific operation
      
     10.5.1 View all ===>View all the tickets
     10.5.2 View  ====> View specific ticket
           Give the ticket details to view --- Ticket no. and train no.(Press enter after giving ticket no. to give train no.)

     10.5.3 Book ticket ===> Book a ticket for the customer
     10.5.4 Modify ===> Modify the class of ticket for the customer
     10.5.5 Cancel booking ===> Cancel the customer ticket
           


11 Files used 
  loginc.txt ===> Login details of customer
  loginag.txt===> Login details of agent
  train1.txt ===> Train A ticket number
  train2.txt ===> Train B ticket number
  train3.txt ===> Train C ticket number
  
  Customer ticket details file
  'cusabc`000'===> Customer named abc ticket details
  'cusert`000'===> Customer named ert ticket details
