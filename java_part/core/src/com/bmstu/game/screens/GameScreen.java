package com.bmstu.game.screens;

import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Box2DDebugRenderer;
import com.badlogic.gdx.physics.box2d.World;
import com.bmstu.game.PPMGame;

import static com.bmstu.game.utils.B2DConstants.PPM;

public class GameScreen extends AbstractScreen {

    OrthographicCamera camera;

    // Box2D
    World world;
    Box2DDebugRenderer b2dr;

    public GameScreen(final PPMGame app){
        super(app);

        this.camera = new OrthographicCamera();
        this.camera.setToOrtho(false, PPMGame.V_WIDTH, PPMGame.V_HEIGHT);

        app.batch.setProjectionMatrix(camera.combined);
        app.shapeBatch.setProjectionMatrix(camera.combined);

        world = new World(new Vector2(0f, 0f), false);
        b2dr = new Box2DDebugRenderer();
    }

    @Override
    public void show() {

    }

    @Override
    public void update(float delta){
        world.step(1f / PPMGame.APP_FPS, 6, 2);
        stage.act(delta);
    }

    @Override
    public void render(float delta){
        super.render(delta);
        // PPM - pixels per meter, для конвертации между пикселями и метрами
        b2dr.render(world, camera.combined.cpy().scl(PPM));
        stage.draw();
    }

    @Override
    public void pause() {

    }

    @Override
    public void resume() {

    }

    @Override
    public void hide() {

    }

    @Override
    public void dispose() {
        super.dispose();
        world.dispose();
    }
}
