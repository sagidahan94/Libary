package bgu.spl.net.impl.stomp.suppliers;

import bgu.spl.net.impl.stomp.StompMessagingProtocolImp;
import java.util.function.Supplier;

public class StompMessageProtocolFactory<AbstractFrame> implements Supplier<StompMessagingProtocolImp<AbstractFrame>> {
    public StompMessageProtocolFactory(){}
    @Override
    public StompMessagingProtocolImp<AbstractFrame> get() {
        return new StompMessagingProtocolImp<AbstractFrame>();
    }
}
