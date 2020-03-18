
vector<Balloon *> destroybhex;			
BalloonMap::iterator it;
vector<Balloon *>::iterator itvhex;	

vector<Hexa *> destroybhexhex;			
BalloonMap::iterator ithex;
vector<Hexa *>::iterator itvhexhex;



void HexaControl(){
	Hexa *b;
    
    if (Hexas.size() == 0) {
    }
    else{
	  for (ithex = Hexas.begin(); ithex!= Hexas.end(); ++ithex) {
		  b = (Hexa *)((*ithex).second);
		  b->Draw();
		  if(b->playerHit(igrac)){
			  if(lives>1){
				  switch(size(tst)){
					case 1:
						PlaySound("Sounds/playerhit1.wav", NULL, SND_ASYNC);
						break;
					case 2:
						PlaySound("Sounds/playerhit2.wav", NULL, SND_ASYNC);
						break;
					case 3:
						PlaySound("Sounds/playerhit3.wav", NULL, SND_ASYNC);
						break;
					case 4:
						PlaySound("Sounds/playerhit4.wav", NULL, SND_ASYNC);
						break;
				}
			  }
			  else PlaySound("Sounds/gameover.wav", NULL, SND_ASYNC);
			  lives--;
			  igrac->location[0]=SCREENMAXX/2;
			  arrow1x1=-150;
			  arrow2x1=-150;
			  hit=true;
			  break;
		  }
		  if(b->ArrowCheck(arrow1x1,arrow1y)){
			arrow1x1=-150;
			shoot1=false;
			destroybhex.push_back(b);
			points+=b->hexasize*10;
			if(b->hexasize<4){
				SYSTEMTIME systime;
				GetSystemTime(&systime);
				int ID = glutGet(GLUT_ELAPSED_TIME);
				Hexa *l, *r;
				l = new Hexa(b->hexasize+1,ID,-20);
				l->location[0]=b->location[0];
				l->location[1]=b->location[1];
				Hexas[ID] = l;
				int ID2 = glutGet(GLUT_ELAPSED_TIME)+1;
				r = new Hexa(b->hexasize+1,ID2,20);
				r->location[0]=b->location[0];
				r->location[1]=b->location[1];
				Hexas[ID2] = r;
			}
		  }
		  if(b->ArrowCheck(arrow2x1,arrow2y)){
			arrow2x1=-150;
			shoot2=false;
			destroybhex.push_back(b);
			points+=b->hexasize*10;
			if(b->hexasize<4){
				SYSTEMTIME systime;
				GetSystemTime(&systime);
				int ID = glutGet(GLUT_ELAPSED_TIME);
				Hexa *l, *r;
				l = new Hexa(b->hexasize+1,ID,-20);
				l->location[0]=b->location[0];
				l->location[1]=b->location[1];
				Hexas[ID] = l;
				int ID2 = glutGet(GLUT_ELAPSED_TIME)+1;
				r = new Hexa(b->hexasize+1,ID2,20);
				r->location[0]=b->location[0];
				r->location[1]=b->location[1];
				Hexas[ID2] = r;
			}
		  }
		}
	}
	if(hit){ Hexas.clear(); hit=false;}
	for (itvhex = destroybhex.begin(); itvhex!= destroybhex.end(); ++itvhex){
	    if (Hexas.size() == 0) break;
		b =((Hexa *)(*itvhex));
		Hexas.erase(b->ID);
	}
}