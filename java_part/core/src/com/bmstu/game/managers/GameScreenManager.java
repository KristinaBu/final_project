package com.bmstu.game.managers;

import com.bmstu.game.PPMGame;
import com.bmstu.game.screens.AbstractScreen;
import com.bmstu.game.screens.GameScreen;

import java.util.HashMap;

public class GameScreenManager {
    private final PPMGame app;
    private HashMap<STATE, AbstractScreen> gameScreens;
    public enum STATE {
        MAIN_MENU,
        PLAY,
        SETTINGS
    }
    public GameScreenManager(final PPMGame app){
        this.app = app;

        initGameScreens();
        setScreen(STATE.PLAY);
    }

    private void initGameScreens(){
        this.gameScreens = new HashMap<STATE, AbstractScreen>();
        this.gameScreens.put(STATE.PLAY, new GameScreen(app));
    }

    public void setScreen(STATE nextScreen){
        app.setScreen(gameScreens.get(nextScreen));
    }

    public void dispose(){
        for(AbstractScreen screen : gameScreens.values()){
            if (screen != null){
                screen.dispose();
            }
        }
    }

}
