package com.bmstu.game;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.bmstu.game.managers.GameScreenManager;


public class PPMGame extends Game {
	// Application variables
	public static String APP_TITLE = "Pew Pew Meow";
	public static double APP_VERSION = 0.1;
	public static int APP_DESKTOP_WIDTH = 720;
	public static int APP_DESKTOP_HEIGHT = 480;
	public static int APP_FPS = 60;

	// Game variables
	public static int V_WIDTH = 720;
	public static int V_HEIGHT = 420;

	// Managers
	public GameScreenManager gsm;
	public AssetManager assets;

	// Batches
	public SpriteBatch batch;
	public ShapeRenderer shapeBatch;



	@Override
	public void create () {
		gsm = new GameScreenManager(this);
		assets = new AssetManager();
		batch = new SpriteBatch();
		shapeBatch = new ShapeRenderer();
	}

	@Override
	public void render () {
		super.render();
	}
	
	@Override
	public void dispose () {
		batch.dispose();
		shapeBatch.dispose();
		assets.dispose();
	}
}
