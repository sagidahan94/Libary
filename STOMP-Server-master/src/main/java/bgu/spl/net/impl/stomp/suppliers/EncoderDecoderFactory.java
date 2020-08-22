package bgu.spl.net.impl.stomp.suppliers;

import bgu.spl.net.impl.MessageEncoderDecoderImpl;

import java.util.function.Supplier;

public class EncoderDecoderFactory<AbstractFrame> implements Supplier<MessageEncoderDecoderImpl<AbstractFrame>> {
    public EncoderDecoderFactory(){}
    @Override
    public MessageEncoderDecoderImpl<AbstractFrame> get() {
        return new MessageEncoderDecoderImpl<AbstractFrame>();
    }
}
