import java.io.*;
import java.net.*;


class MsgUDPServer {
    public static void main(String[] args) throws Exception {
        byte[] rData = new byte[1024];
        byte [] sData = new byte[1024];
        String msg="";
        DatagramSocket ss = new DatagramSocket(9876);
        while (true) { 
            DatagramPacket rPacket = new DatagramPacket(rData,rData.length);
            ss.receive(rPacket);
            String m[] ={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
            int i = (int)(Math.random()*m.length);
            msg = m[i];
            sData = msg.getBytes();
            InetAddress IP = rPacket.getAddress();
            int port = rPacket.getPort();
            DatagramPacket sPacket = new DatagramPacket(sData,sData.length,IP,port);
            ss.send(sPacket);
        }        
    }
}
