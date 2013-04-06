using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Diagnostics;
using FantasticBox2D;
using System.Windows.Media;

namespace FantasticProject.Projects
{
    public partial class Box2DDemo : PhoneApplicationPage
    {
        private B2WorldPRT world;
        private B2BodyPRT body;

        public Box2DDemo()
        {
            InitializeComponent();
            this.Loaded += Box2DDemo_Loaded;
            CompositionTarget.Rendering += OnCompositionTargetRendering;
        }

        private void Box2DDemo_Loaded(object sender, RoutedEventArgs e)
        {
            CreateTestWorld();
        }

        private void OnCompositionTargetRendering(object sender, EventArgs e)
        {
            // simulation
            if (world != null)
            {
                float timeStep = 1.0f / 30.0f;
                int velocityIterations = 6;
                int positionIterations = 2;

                world.Step(timeStep, velocityIterations, positionIterations);
                B2Vec2PRT position = body.GetPosition();
                float angle = body.GetAngle();

                Point screenPosition = GetScreenPositionOfBox(position, new Size(10.0f, 10.0f));

                Canvas.SetLeft(TestBox, screenPosition.X);
                Canvas.SetTop(TestBox, screenPosition.Y);
                TextBoxRotation.Angle = angle * 180.0f / 3.14f;

                //Debug.WriteLine(String.Format("{0:0.00} {1:0.00} {2:0.00}", screenPosition.X, screenPosition.Y, angle));
            }
        }

        private void CreateTestWorld()
        {
            // create test world
            B2Vec2PRT gravity = new B2Vec2PRT(0.0f, -20.0f);
            bool doSleep = true;
            this.world = new B2WorldPRT(gravity, doSleep);

            // creating a ground box
            B2BodyDefPRT groundBodyDef = new B2BodyDefPRT();
            groundBodyDef.Position.Set(240.0f, -200.0f);
            B2BodyPRT groundBody = world.CreateBody(groundBodyDef);
            B2PolygonShapePRT groundBox = new B2PolygonShapePRT();
            groundBox.SetAsBox(50.0f, 10.0f);
            groundBody.CreateFixture(groundBox, 0.0f);

            // create a dynamic body
            B2BodyDefPRT bodyDef = new B2BodyDefPRT();
            bodyDef.Type = B2BodyTypePRT.B2_DynamicBody;
            bodyDef.Position.Set(240.0f, -20.0f);
            bodyDef.Angle = 60.0f * 3.14f / 180.0f;
            this.body = world.CreateBody(bodyDef);
            B2PolygonShapePRT dynamicBox = new B2PolygonShapePRT();
            dynamicBox.SetAsBox(10.0f, 10.0f);
            B2FixtureDefPRT fixtureDef = new B2FixtureDefPRT();
            fixtureDef.Shape = dynamicBox;
            fixtureDef.Density = 1.0f;
            fixtureDef.Friction = 0.3f;
            fixtureDef.Restitution = 0.4f;
            body.CreateFixture(fixtureDef);
        }

        Point PhyPointToScreenPoint(B2Vec2PRT phyPoint)
        {
            return new Point(phyPoint.X, -phyPoint.Y);
        }

        Point GetScreenPositionOfBox(B2Vec2PRT phyPos, Size halfSize)
        {
            Point phyPosPoint = PhyPointToScreenPoint(phyPos);
            return new Point(phyPosPoint.X - halfSize.Width, phyPosPoint.Y - halfSize.Height);
        }

        private void Box2DCanvas_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            Debug.WriteLine("Box2DCanvas_Tap");
            CreateTestWorld();
        }
    }
}