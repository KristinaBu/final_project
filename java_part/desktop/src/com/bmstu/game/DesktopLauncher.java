package com.bmstu.game;

import com.badlogic.gdx.Application;
import com.badlogic.gdx.backends.lwjgl3.Lwjgl3Application;
import com.badlogic.gdx.backends.lwjgl3.Lwjgl3ApplicationConfiguration;
import com.bmstu.game.PPMGame;

// Please note that on macOS your application needs to be started with the -XstartOnFirstThread JVM argument
public class DesktopLauncher {
	public static void main (String[] arg) {
		Lwjgl3ApplicationConfiguration config = new Lwjgl3ApplicationConfiguration();
		config.setTitle(PPMGame.APP_TITLE);
		config.setWindowedMode(PPMGame.APP_DESKTOP_WIDTH, PPMGame.APP_DESKTOP_HEIGHT);
		config.setForegroundFPS(PPMGame.APP_FPS);
		config.setResizable(false);

		new Lwjgl3Application(new PPMGame(), config);
	}
}
