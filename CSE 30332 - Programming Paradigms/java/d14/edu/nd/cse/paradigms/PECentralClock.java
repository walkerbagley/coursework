package edu.nd.cse.paradigms;

import java.util.Timer;
import java.util.TimerTask;

public class PECentralClock {
    protected PEEngine engine;
    private int rate;

    public PECentralClock(PEEngine engine, int rate) {
        this.engine = engine;
        this.rate = rate;
        this.run();
    }

    public void run() {
        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                engine.tick();
            }
        }, 0, this.rate);
    }

}