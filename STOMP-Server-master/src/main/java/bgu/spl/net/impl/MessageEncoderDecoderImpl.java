package bgu.spl.net.impl;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.api.messages.ClientFrames.*;
import jdk.nashorn.internal.ir.WhileNode;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class MessageEncoderDecoderImpl<T> implements MessageEncoderDecoder<AbstractFrame> {

    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;
    private final byte endOfFrame = '\u0000';

    @Override
    public AbstractFrame decodeNextByte(byte nextByte) {
        //notice that the top 128 ascii characters have the same representation as their utf-8 counterparts
        //this allow us to do the following comparison
        if (nextByte == endOfFrame) {
            return parser(popString());
        }

        pushByte(nextByte);
        return null; //not a full message yet
    }

    @Override
    public byte[] encode(AbstractFrame message) {
        return message.toString().getBytes();
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }

        bytes[len++] = nextByte;
    }

    private String popString() {
        //notice that we explicitly requesting that the string will be decoded from UTF-8
        //this is not actually required as it is the default encoding in java.
        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);
        len = 0;
        //bytes = new byte[1 << 10];
        return result;
    }

    private AbstractFrame parser(String result) {
        //TODO: need to fix the the problem in the Send frame which the body is not included in the post-parsing
        System.out.println("Parser started");
        int index = 0;
        String[] parameters = result.split(System.lineSeparator());
        String command = parameters[0];
        String body = "";
        List<String> headers = new LinkedList<>();
        for (String param : parameters) {
            if (index != 0) {
                try {
                    if( !(command.equals("SEND") && index==parameters.length-1))
                    {   if(param.contains(":")){ headers.add(param.split(":")[1]);} }
                    }
                catch(Exception ex)
                    {
                        //body = param;
                    }
                }
            index++;
            }
        if(command.equals("SEND")){
            body = parameters[parameters.length-1];
        }
        //region old version
//            index++;

/*        String body = "";
        try {
            body = parameters[index];
        } catch (Exception e) {
            body = "";
        }*/
//endregion
        AbstractFrame frame = InterpretClientFrame(command, headers, body);
        System.out.println("Received Message");
        System.out.println("----------------");
        System.out.println(frame.toString());
        return frame;
    }

    private AbstractFrame InterpretClientFrame(String command, List<String> headers, String body) {
        AbstractFrame frame = null;
        switch (command) {
            case "CONNECT": {
                frame = new Connect(headers.get(0), headers.get(1), headers.get(2), headers.get(3));
                break;
            }
            case "SUBSCRIBE": {
                frame = new Subscribe(headers.get(0), headers.get(1), headers.get(2));
                break;
            }
            case "UNSUBSCRIBE": {
                frame = new Unsbscribe(headers.get(0), headers.get(1));
                break;
            }
            case "SEND": {
                if(body.contains("book status") || body.contains("Book status")){body = "Book status";}
                frame = new Send(headers.get(0), body);
                break;
            }
            case "DISCONNECT": {
                frame = new Disconnect(headers.get(0));
                break;
            }
        }
        return frame;
    }
}
