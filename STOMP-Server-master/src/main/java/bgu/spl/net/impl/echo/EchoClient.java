package bgu.spl.net.impl.echo;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.api.messages.ClientFrames.*;
import bgu.spl.net.api.messages.ServerFrames.Message;
import bgu.spl.net.api.messages.ServerFrames.Receipt;
import bgu.spl.net.impl.MessageEncoderDecoderImpl;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class EchoClient {

    public static void main(String[] args) throws IOException {
        //region
        //Message msg = new Message("78", "000245", "sci-fi", "");
        //Receipt receipt = new Receipt("78");
        //endregion

/*        for(int i=0;i<headers.size();i++)
        {
            headers.set(i,headers.get(i).split(":")[1]);
        }*/
        //    while ()
/*        if (args.length == 0) {
            args = new String[]{"localhost", "hello"};
        }

        if (args.length < 2) {
            System.out.println("you must supply two arguments: host, message");
            System.exit(1);
        }

        //BufferedReader and BufferedWriter automatically using UTF-8 encoding
        try (Socket sock = new Socket(args[0], 7777);
                BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()))) {

            System.out.println("sending message to server");
            out.write(args[1]);
            out.newLine();
            out.flush();

            System.out.println("awaiting response");
            String line = in.readLine();
            System.out.println("message from server: " + line);
        }*/
    }

}
