import java.io.*;
import java.net.*;


class MsgTCPClient {
    public static void main(String[] args) throws Exception {
        String msg;

        Socket s2 = new Socket("localhost",80);
        BufferedReader d2 = new BufferedReader(new InputStreamReader(s2.getInputStream()));
        msg = d2.readLine();
        System.out.println("The day is "+msg);
        s2.close();
    }
}