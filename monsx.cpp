/*******************
Allegro Newbie Tutorial

by
LoomSoft

http://loomsoft.net
email: jay@loomsoft.net
*******************/
/* Allegro Newbie Tutorial : Lesson 6 - Using Timers
 *
 * In this lesson we will learn how to use timers in order 
 * to make Allegro programs run at the same speed on any system
 */

#include <allegro.h> // You must include the Allegro Header file
#include <stdio.h>

/* This is the timer function and integer.
 * Since they will be used throughout the entire program, basically 
 * being tested each loop, we will just declare them globally. 
 * There really isn't any waste of memory seeing as how they are used so often.
 */

struct OBJECT {
	double x, y;
};


volatile long speed_counter = 0; //A long integer which will store the value of the
								 //speed counter.
volatile long test_counter = 0;

void increment_speed_counter() //A function to increment the speed counter
{
	speed_counter++; // This will just increment the speed counter by one. :)
	test_counter++;
}
END_OF_FUNCTION(increment_speed_counter); //Make sure you tell it that it's the end of the

										  //function


/* Set up the general main function, and init allegro. */
int main(int argc, char *argv[])
{
	allegro_init(); // Initialize Allegro
	install_keyboard(); // Initialize keyboard routines
	
	/* You need to tell allegro to install the timer routines in order to use timers. */
	install_timer(); // Initialize the timer routines
	
	/* Ok, now heres some new code. First, we need to, as the function suggests, 
	 * lock our speed counter. Then, we need to lock the function which increments 
	 * the speed counter. Locking is used maily for historical reasons (eg: Pure DOS
	 * Allegro applications) It doesn't hurt to lock the variable and function anyway
	 * even if we're not running DOS only mode.
	 */
	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's
	LOCK_FUNCTION(increment_speed_counter);//speed.
	
	/* Next, we need to tell the computer to keep incrementing the speed counter 
	 * independent of what the program is currenlty doing with the following function. 
	 * We will also tell it how fast to go. The argument to the function BPS_TO_TIMER 
	 * will tell the computer how many 'beat's per second. Experiment with this number 
	 * to get the overall 'speed' you would like in your game. 60 works well, generally.
	 */		
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(60)); //Set our BPS
//	install_int_ex(test_counter, BPS_TO_TIMER(60));
	
	/* This next chunk of code is exactly the same as lesson 5. Create a buffer, 
	 * and a bitmap (and load an image into the bitmap).
	 */
	set_color_depth(32); // Set the color depth
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480 
//	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640,480,0,0); // Change our graphics mode to 640x480 	

	BITMAP *monsquaz; //Declare a BITMAP called monsquaz
	monsquaz = load_bitmap("picture.bmp", NULL); // Load our picture

	BITMAP *sunsetbg = load_bitmap("sunsetbg.bmp", NULL);
	BITMAP *greenarrowbg = load_bitmap("greenarrowbg.bmp", NULL);
	BITMAP *pinkarrowbg = load_bitmap("pinkarrowbg.bmp", NULL);

	BITMAP *d_gallo = load_bitmap("d_gallo.bmp", NULL);
	BITMAP *pinkarrow = load_bitmap("pinkarrow.bmp", NULL);
	BITMAP *greenarrow = load_bitmap("greenarrow.bmp", NULL);

   if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
      allegro_message("Error initialising sound system\n%s\n", allegro_error);
      return 1;
   }


	SAMPLE *music = load_wav("music3.wav");


	BITMAP *buffer; //Declare a BITMAP called buffer.
	
	buffer = create_bitmap(640,480); //Create an empty bitmap.
			
	/* Declare some integers for later use */
	double monsquaz_x = 200; // Holds our picture's X coorinate
	double monsquaz_y = 480; // Holds our picture's Y coordinate
	double monsquaz_width = 203;
	double monsquaz_height = 405;


	int musicst=1;
	int firstrun=1;

	int monsquaz_a=0, monsquaz_b=0, counta=0, countb=0;
	int usebg=0;

	double gc_x, gc_y, gc_radius;
	double yc_x, yc_y, yc_radius;

	double bg_red=0, bg_blue=0;

	int r_amount=200;

	OBJECT arrow_a, arrow_b;
	OBJECT dgallo_a, dgallo_b;
	
	arrow_a.x=120;
	arrow_a.y=240;

	arrow_b.x=330;
	arrow_b.y=349;

	dgallo_a.x=0;
	dgallo_a.y=220;
	
	dgallo_b.x=640-93;
	dgallo_b.y=220+50;

//	while(test_counter<30) play_sample(music, 0, 128, 1000, 1);

					
	while(!key[KEY_ESC]) //If the user hits escape, quit the program
	{
	
		/* Here is the last part of the timer routines. We want to separate the logic
		 * and the drawing portions of the program, so we crate a while loop to test 
		 * for the value of speed counter
							
		 * While the value is greater than 0 it will do the logical part, and once it 
		 * drops down to equal to (or lower than) 0, it will draw the screen. Generally 
		 * the values of speed_counter fluctuate only between 0 and 1
		 *
		 * What this does is allow for the computer to do the all the logical part of the 
		 * program before it blits to the screen, so you don't miss any keypresses, etc.
		 */
		while(speed_counter > 0)
		{
			/* This part of the code, the "series of tests" is considered the logical 
			 * part of the program. It figures out all calculations, etc. The non-logical 
			 * part of the program would be any image blitting, or sprite(ing). Therefore, 
			 * since it is a logical part of the program, it will be within the while loop 
			 * that tests to see if the counter is greater than 0. 
			 */
			
			// first part			

			if(musicst==1){
				stop_sample(music);
				play_sample(music, 255, 128, 1000, 1);
				musicst=0;
			}

			if(monsquaz_a==0) monsquaz_y=monsquaz_y-7.370;
			if(monsquaz_y<=-405 and monsquaz_x==200) monsquaz_a=1;

			if(usebg==0){
				if(arrow_a.y>160) arrow_a.y=arrow_a.y-0.66;
				if(arrow_b.y>0) arrow_b.y=arrow_b.y-2.88;
			}

			if(monsquaz_a==1){
				monsquaz_y=75;
				monsquaz_a=2;
				monsquaz_b=1;
				dgallo_a.y=220;
				dgallo_b.y=220+50;
				usebg++;
			}

			// second part

			if(monsquaz_b==1) {
				//120 / 4 
				//move 50 away from from y75
				if(monsquaz_y<75+50) monsquaz_y=monsquaz_y+1.66;
				else counta=1;
				
				//move x
				if(monsquaz_x>200-50) monsquaz_x=monsquaz_x-1.66;
				else countb=1;

				//dgallo
				//dgallo_a.y++;
				//if(dgallo_a.y>220)
				dgallo_a.y=dgallo_a.y+1.66;
				dgallo_b.y=dgallo_b.y-1.66;

				if(counta==1 and countb==1) monsquaz_b++;		
			}

			if((counta==1 and countb==1) and monsquaz_b==2){
				monsquaz_x=200-50;
				monsquaz_y=75+50;

				dgallo_a.y=220+50;
				dgallo_b.y=220;
				
				counta=0;
				countb=0;
			}

			if(monsquaz_b==2) {
				//120 / 4 
				//move 50 away from from y75
				if(monsquaz_y>75) monsquaz_y=monsquaz_y-1.66;
				else counta=1;
				
				//move x
				if(monsquaz_x<200) monsquaz_x=monsquaz_x+1.66;
				else countb=1;

				if(dgallo_a.y>220) dgallo_a.y=dgallo_a.y-1.66;
				if(dgallo_b.y<220+50) dgallo_b.y=dgallo_b.y+1.66;

				if(counta==1 and countb==1) monsquaz_b++;		
			}

			if((counta==1 and countb==1) and monsquaz_b==3){
				monsquaz_x=200;
				monsquaz_y=75;

				dgallo_a.y=220;
				dgallo_b.y=220+50;
				
				counta=0;
				countb=0;
			}

			if(monsquaz_b==3) {
				//120 / 4 
				//move 50 away from from y75
				if(monsquaz_y<75+50) monsquaz_y=monsquaz_y+1.68;
				else counta=1;
				
				//move x
				if(monsquaz_x<200+50) monsquaz_x=monsquaz_x+1.68;
				else countb=1;

				if(dgallo_a.y<220+50) dgallo_a.y=dgallo_a.y+1.66;
				if(dgallo_b.y>220) dgallo_b.y=dgallo_b.y-1.66;

				if(counta==1 and countb==1) monsquaz_b++;		
			}

			if((counta==1 and countb==1) and monsquaz_b==4){
				monsquaz_x=200+50;
				monsquaz_y=75+50;

				dgallo_a.y=220+50;
				dgallo_b.y=220;
				
				counta=0;
				countb=0;
			}

			if(monsquaz_b==4) {
				//120 / 4 
				//move 50 away from from y75
				if(monsquaz_y>75) monsquaz_y=monsquaz_y-1.685;
				else counta=1;
				
				//move x
				if(monsquaz_x>200) monsquaz_x=monsquaz_x-1.685;
				else countb=1;

				if(dgallo_a.y>220) dgallo_a.y=dgallo_a.y-1.66;
				if(dgallo_b.y<220+50) dgallo_b.y=dgallo_b.y+1.66;

				if(counta==1 and countb==1) monsquaz_b++;		
			}

			// init third part
			if((counta==1 and countb==1) and monsquaz_b==5){
				monsquaz_x=200;
				monsquaz_y=-410;
				usebg++;
				
				counta=0;
				countb=0;
			}

			// third part starts here
			if(monsquaz_b==5){
				if(monsquaz_y<480) monsquaz_y=monsquaz_y+7.3837;
				else counta=1;

				arrow_a.y=arrow_a.y+0.66;
				arrow_b.y=arrow_b.y+2.88;

			}

			if(monsquaz_b==5 and counta==1){
				monsquaz_x=200;
				monsquaz_y=330;
				usebg=4;
				counta=0;
				countb=0;
				
				gc_x=640/2;
				gc_y=480/2;
				gc_radius=300;

				yc_x=640/2;
				yc_y=480/2;
				yc_radius=0;

				bg_red=0;
				bg_blue=128;


				monsquaz_b++;
			}

			if(monsquaz_b==6){
				// w203 h405 
				monsquaz_width=monsquaz_width+1.69;//+0.065;
				monsquaz_height=monsquaz_height+3.37;//+0.065;
				
				if(monsquaz_x>20) monsquaz_x=monsquaz_x-((200-20)/120);
				if(monsquaz_y>0) monsquaz_y=monsquaz_y-2.75;
				
				if(countb<2){
					if(gc_radius>0) gc_radius=gc_radius-(300/30);
					else countb++;
					if(yc_radius<300) yc_radius=yc_radius+(300/30);
					else countb++;

					bg_blue=bg_blue-(128/30);
					bg_red=bg_red+((r_amount)/30);
				}
				else{
					if(yc_radius>0) yc_radius=yc_radius-(300/30);
					else countb++;
					if(gc_radius<300) gc_radius=gc_radius+(300/30);
					else countb++;

					bg_blue=bg_blue+(128/30);
					bg_red=bg_red-((r_amount)/30);

					if(countb==4) countb=0;
				}
				
				if(monsquaz_width>=204*2 and monsquaz_height>=405*2) counta=1;
			}
			
//			if((monsquaz_b==6 and counta==1) or test_counter>=480){
//			if(test_counter>=480){
			if(test_counter>=480 or firstrun==1 or key[KEY_P]){
				arrow_a.x=120;
				arrow_a.y=240;

				arrow_b.x=330;
				arrow_b.y=349;

				dgallo_a.x=0;
				dgallo_a.y=220;
	
				dgallo_b.x=640-93;
				dgallo_b.y=220+50;

				usebg=0;
				monsquaz_a=0;
				monsquaz_b=0;
				counta=0;
				countb=0;

				monsquaz_x = 200; // Holds our picture's X coorinate
				monsquaz_y = 480; // Holds our picture's Y coordinate
				monsquaz_width = 203;
				monsquaz_height = 405;
			
				test_counter=0;

				if(key[KEY_P]) musicst=1;

				if(firstrun==1){
//					musicst=1;
					firstrun=0;
					speed_counter=0;
				}
//				stop_sample(music);
			}

			speed_counter --;
		} // This is the closing bracket for the (speed_counter > 0) test
		
		/* Notice that we do all blitting and drawing in this next section of code. 
		 * We only want to draw when the speed counter is less than 0, when the computer 
		 * is finished doing enough logic. Make sure you put it before the closing bracket
		 * for the (key[KEY_ESC]) test, or else nothing will be drawn (until you hit Escape,
		 * and then the program will shut down so fast you still won't be able to see anything!
		 */
		if(usebg==0) blit(greenarrowbg, buffer,0,0,0,0,640,480);
		if(usebg==1) blit(sunsetbg, buffer,0,0,0,0,640,480);
		if(usebg==2) blit(pinkarrowbg, buffer,0,0,0,0,640,480);

		if(usebg==0){
			draw_sprite(buffer, greenarrow, arrow_a.x, arrow_a.y);
			draw_sprite(buffer, greenarrow, arrow_b.x, arrow_b.y);
		}

		if(usebg==1){
			draw_sprite(buffer, d_gallo, dgallo_a.x, dgallo_a.y);
			draw_sprite(buffer, d_gallo, dgallo_b.x, dgallo_b.y);
		}

		if(usebg==2){
			draw_sprite(buffer, pinkarrow, arrow_a.x, arrow_a.y);
			draw_sprite(buffer, pinkarrow, arrow_b.x, arrow_b.y);
		}

		//stretch_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int w, int h);
		//circle(BITMAP *bmp, int x, int y, int radius, int color);
		if(usebg==4){
			rectfill(buffer, 0, 0, 640, 480, makecol(bg_red,0,bg_blue) );
			circle(buffer, gc_x, gc_y, gc_radius, makecol(0,255,0));
			circle(buffer, yc_x, yc_y, yc_radius, makecol(255,255,0));
			stretch_sprite(buffer, monsquaz, monsquaz_x, monsquaz_y, monsquaz_width, monsquaz_height);
		}

		//rotate_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);

		if(usebg!=4){
			draw_sprite(buffer, monsquaz, monsquaz_x, monsquaz_y); //Draw the picture to the buffer
			rotate_sprite(buffer, greenarrow, monsquaz_x+117, monsquaz_y+242, ftofix(64));
		}

		blit(buffer, screen, 0,0,0,0,640,480); //Draw the buffer to the screen
		clear_bitmap(buffer); // Clear the contents of the buffer bitmap 
		rest(22);

	} // This is the closing bracket for the (key[KEY_ESC]) test

	/* Do all the destroying, finishing parts of the program. */
	destroy_bitmap(monsquaz); //Release the bitmap data
	destroy_bitmap(buffer); //Release the bitmap data 
	return 0; // Exit with no errors
}
END_OF_MAIN() // This must be called right after the closing bracket of your MAIN function.
			  // It is Allegro specific.
