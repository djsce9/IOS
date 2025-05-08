import java.io.*;
import java.net.*;

class MsgTCPServer {
    public static void main(String[] args) throws Exception {
        String s;
        ServerSocket ss1 = new ServerSocket(80);
        while(true)
        {
            Socket s1 = ss1.accept();
            String m[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
            int i = (int)(Math.random()*m.length);
            s = m[i];
            PrintStream d1 = new PrintStream(s1.getOutputStream());
            d1.println(s);
        }
    }
}