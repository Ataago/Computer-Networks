//Write a Program in C/ C++ for congestion control using Leaky Bucket algorithm

#include<stdlib.h> 
#include<stdio.h> 
#include<math.h>

int main() 
{
    int packets[5], i, j, clk, b_size, o_rate, p_sz_rm = 0, p_sz, p_time; 
    system("clear");

    for(i=0;i<5;i++)
    {
        packets[i] = random()%6*10;  //generates random packet size
        printf("\nPacket %d: %dB", i+1, packets[i]);
    }
    printf("\n Enter the output rate (Bps): "); 
    scanf("%d",&o_rate);

    printf("\n Enter the Bucket size: ");
    scanf("%d",&b_size);

    for(i=0;i<5;++i)    //Arival of each packet
    {
        printf("\n\nRecieved Packet %d of size: %dB\n",i+1, packets[i]); //Packet recieved info
        if( (packets[i] + p_sz_rm) > b_size)    //Buffer overflow
        {
            if(packets[i] > b_size)     //packet itself is greater than bucket size (GET ME SMALL PACKETS NA)
                printf("\n Incoming packet size (%d) is Greater than Bucket capacity Rejected",packets[i]);
            else    //Bucket is full (PLEASE INCREASE THE LEAKYNESS)
                printf("\n Bucket capacity exceeded Rejected");
        }
        else //Packet pushed into Bucket
        {
            p_sz = packets[i];
            p_sz_rm += p_sz;
            printf("\n Bytes Remaining: %d of %d", p_sz_rm, b_size);    //Bucket(buffer) status

            p_time = random()%6;  //generate random time for next packet
            printf("\n Next packet will come at: %d sec",p_time);

            for(clk = 0; clk <= p_time; clk += 1)   //every sec
            {
                printf("\n Time Left: %d sec",(p_time - clk)); 
                sleep(1);
                if(p_sz_rm)     //Bucket is not empty
                {
                    if(p_sz_rm > o_rate)    //buffer has more bytes than the leak rate(o_rate)
                    {
                        printf(" -- Transmited %dB", o_rate);   //bucket leaks every sec at o_rate
                        p_sz_rm -= o_rate;                      //Bytes left next sec
                    }
                    else   //Buffer has lesser Bytes than the Leak Rate.
                    {
                        printf(" -- Transmited %dB", p_sz_rm);  //Bucket is empty
                        p_sz_rm = 0;
                    }
                    printf(" -- Bytes Remaining: %d of %d",p_sz_rm, b_size);    //Bucket status
                } 
                else        //Bucket is empty
                {
                    printf("--No packet to transmit");
                }
            } //1 sec over
        }   //end of else (ith Packet is in the bucket)
    }   //Next Packet
    printf("\n\n"); 
    return 0;
}