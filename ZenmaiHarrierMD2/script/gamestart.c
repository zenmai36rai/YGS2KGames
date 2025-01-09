
void main(){
	int x,y;					//	マイキャラの座標を保持するための変数
	int vx,vy;					//	マイキャラの速度(ジャンプ中)
	int j;						//	二段ジャンプのためのフラグ
	int bx[10],by[10],bz[10],bb[10];		//	敵キャラの座標と有効かどうかを保持するための変数
	int wx[10],wy[10],wz[10],ww[10];		//	壁の座標
	int gx[10],gy[10],gz[10],gg[10];		//	草の座標
	int lx[10],ly[10],lz[10],ll[10];		//	ラインの座標
	//	bb[n]が0ならば空き、1ならば横移動中。2ならば縦移動中、3ならば斜め移動を表す。
	int tx[3],ty[3],tz[3],tvx[3],tvy[3],tvz[3],tt[3];
	int sx[3],sy[3],sz[3],st[3];			//	ショット変数
	int score;
	int isDead;
	int i;
	int n;
	int tail;
	int bg;						//	背景の種類
	int ii;
	int dragon;					//	ドラゴンの出るスコア
	int zoom,xbuf,ybuf;
	int ex[10],ey[10],ez[10],ee[10],ei;		//	爆発用変数
	int zanki;
	int time;
	int zz;

	初期化処理();
	ゲームスタート表示();
	PlayMIDI();

	zanki = 3;
	score = 0;
	dragon = 50000;
	x = 240; y= 400;						//	マイキャラの座標初期化
	vx = 0;	 vy = 0;						//	マイキャラの速度は０
	j = 0;								//	はじめはジャンプしていない
	isDead = 0;							//	最初は生きてる

	for(i=0;i<10;i++) bb[i]=0;				//	全ブロック初期化
	for(i=0;i<3;i++) tt[i]=0;				//	弾の初期化
	for(i=0;i<3;i++) st[i]=0;				//	ショットの初期化
	for(i=0;i<10;i++) ee[i]=0;
	for(i=0;i<10;i++) ww[i]=0;				//	壁初期化
	for(i=0;i<10;i++) gg[i]=0;				//	草初期化
	for(i=0;i<10;i++) ll[i]=0;				//	ライン初期化
	
	bx = 640; by = 400;					//	敵キャラの座標初期化
	bg=1;
	time=0;
	loop {
		time++;
		ClearSecondary();				//	画面クリア
//		↑は、↓でＢＧを表示するので不要
		ＢＧ表示(2,x,y);
		// Z-orderが自分より奥のものを先に表示
		for(zz = 480; zz>0; zz--){
			if((ll[i] != 0) && (zz == lz[i])){
				ライン表示(x,y,lx[i],ly[i],lz[i]);
			}
			for(i=0;i<3;i++) {
				// ショット表示
				if((st[i] != 0) && (sz[i] == zz)) {
					zoom=65536;
					xbuf = x;
					if( sz[i] != 0 ) {
						zoom = (120 << 16) / sz[i];
					}
					xbuf = (sx[i] * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
					ybuf = (sy[i] * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
					BltRectR(0,xbuf,ybuf,0,240,48,48,zoom,zoom);			//	０番のプレーンの(0,192)から48×48を表示
					sz[i] = sz[i] + 16;
					if(sz[i] > 480) {
						st[i] = 0;
					}
				}
			}
			for(i=0;i<10;i++){
				if((ee[i]!=0) && (ez[i] == zz)) {
					爆発表示(x,y,ex[i],ey[i],ez[i],ee[i]);
					ee[i]--;
				}
			}
			for(i=0;i<10;i++){
				if((ww[i]!=0) && (wz[i] == zz)) { 迷路表示(x,y,wx[i],wy[i],wz[i]); }
			}
			for(i=0;i<10;i++){
				if((gg[i]!=0) && (gz[i] == zz)) { 草表示(x,y,gx[i],gy[i],gz[i]); }
			}
			for(i=0;i<10;i++){
				if ((bb[i]!=0) && (bz[i]==zz)) {
					ブロック表示(x,y,bx[i],by[i],bz[i],bb[i]);
				}
			}
			for(i=0;i<3;i++){
				if (tt[i]!=0) {
					if(tz[i]==zz) {
						弾表示(x,y,tx[i],ty[i],tz[i]);
					}
				}
			}
			if(zz==120){
				マイキャラ表示(x,y);
			}
		}
		// ショットの接触判定
		for(i=0;i<3;i++) {
			for(ii=0;ii<10;ii++){
				if(bb[ii]!=0) {
					if (ショット判定(x,y,sx[i],sy[i],sz[i],bx[ii],by[ii],bz[ii],96)){
						bb[ii] = 0;
						st[i] = 0;
						PlayWave(4);
						for(ei=0;ei<10;ei++){
							ex[ei] = bx[ii];
							ey[ei] = by[ii];
							ez[ei] = bz[ii];
							ee[ei] = 3;
						}
					}
				}
				if(ww[ii]!=0) {
					if (ショット判定(x,y,sx[i],sy[i],sz[i],wx[ii],wy[ii],wz[ii],100)){
						ww[ii] = 0;
						st[i] = 0;
						PlayWave(4);
						for(ei=0;ei<10;ei++){
							ex[ei] = wx[ii];
							ey[ei] = wy[ii];
							ez[ei] = wz[ii];
							ee[ei] = 3;
						}
					}
				}
				if(ll[ii]!=0) {
					if (ショット判定(x,y,sx[i],sy[i],sz[i],lx[ii],ly[ii],lz[ii],100)){
						ll[ii] = 0;
						st[i] = 0;
						PlayWave(4);
						for(ei=0;ei<10;ei++){
							ex[ei] = lx[ii];
							ey[ei] = ly[ii];
							ez[ei] = lz[ii];
							ee[ei] = 3;
						}
					}
				}
			}
		}
		マイキャラ移動(&x,&y,&vx,&vy,&j);
		if (IsPushSpaceKey()) {
			for(i=0;i<3;i++) {
				if(st[i] == 0) {
					PlayWave(0);
					st[i] = 1;
					sx[i] = x - 12;
					sy[i] = y;
					sz[i] = 100;
					break;
				}
			}
		}
		for(i=0;i<10;i++){
			// ライン発生
			if( ll[i]==0 ) {
				// 1/100の確率でライン発生
				if (Rand(80) == 0) ライン発生(&lx[i],&ly[i],&lz[i],&ll[i],time);
			}
			// ライン移動
			lz[i] = lz[i] - 8;
			if(lz[i] <= 60) { lz[i] = 30; ll[i]=0; }
			if( ((i % 3) == 0) && ((ww[i]==0) && (ww[i+1]==0) &&(ww[i+2]==0) &&(ww[i+3]==0) &&(ww[i+4]==0))) {
				// 1/60の確率で壁発生
				if (Rand(60) == 0) {
					壁発生(&wx[i],&wy[i],&wz[i],&ww[i],time);
					for(n=1;n<3;n++){
						if(wx[i] < 120) { tail = 60; } else { tail = -60;}
						wx[i+n] = wx[i] + (tail * n);
						wy[i+n] = wy[i];
						wz[i+n] = wz[i] + (60 * n);
						ww[i+n] = ww[i];
					}
				}
			}
			if( gg[i]==0 ) {
				// 1/100の確率で草発生
				if (Rand(100) == 0) 草発生(&gx[i],&gy[i],&gz[i],&gg[i],time);
			}
			// 壁移動
			wz[i] = wz[i] - 8;
			if(wz[i] <= 60) { wz[i] = 30; ww[i]=0; }
			// 草移動
			gz[i] = gz[i] - 8;
			if(gz[i] <= 60) { gz[i] = 30; gg[i]=0; }
			if ((bb[i]!=0)) {
				ブロック移動(&bx[i],&by[i],&bz[i],&bb[i]);
				if (接触判定(x,y,bx[i],by[i],bz[i])) {isDead = 1;bb[i]=0;}	//	死んだ
			} else {
			//	1/100の確率でブロック発生
				if (Rand(100)==0) ブロック発生(&bx[i],&by[i],&bz[i],&bb[i],time);
			}
		}
		for(i=0;i<3;i++){
			if (tt[i]!=0) {
				弾移動(&tx[i],&ty[i],&tz[i],&tvx[i],&tvy[i],&tvz[i],&tt[i]);
				if (接触判定(x,y,tx[i],ty[i],tz[i])) {isDead = 1;tt[i]=0;}	//	死んだ
			} else {
				for(ii=0;ii<10;ii++){
					// 弾発生
					if ((bb[ii]==2) || (bb[ii]==3)){
						if (Rand(100)==0) {
							弾発生(x,y,bx[ii],by[ii],bz[ii],&tx[i],&ty[i],&tz[i],&tvx[i],&tvy[i],&tvz[i],&tt[i]);
						}
					}
				}
			}
		}
		スコア表示(&score,&zanki);

		halt;								//	画面表示

		if (isDead) {
			PlayWave(5);
			ClearSecondary();					//	画面クリア
			halt;
			zanki--;
			isDead = 0;	// 生き返る
			if(zanki==0){ break; }					//	死んでた？
		}
	}

	StopMIDI();
	ＢＧ表示(2,x,y);
	スコア表示(&score,&zanki);
	ゲームオーバー表示();
}

void 初期化処理(){
	SetFPS(30);					//	フレームレートを３０に
	LoadBitmap("script/doli.bmp",0,1);		//	ドットの読み込み
	LoadBitmap("script/Space_Harrier_0.jpg",1,1);	//	BG2の読み込み
	LoadBitmap("script/Space_Harrier_1.jpg",2,1);	//	BG2の読み込み
	LoadBitmap("script/exp.bmp",6,1);		//	ドットの読み込み
	LoadBitmap("script/wall.bmp",9,1);		//	壁画像の読み込み
	LoadBitmap("script/glass.bmp",10,1);		//	草画像の読み込み
	LoadBitmap("script/hline.bmp",11,1);		//	ライン画像の読み込み
	LoadWave("script/hyupa2.wav",0);		//	ジャンプ音の読み込み
	LoadWave("script/drop.wav",1);			//	落下音の読み込み
	LoadWave("script/gucha.wav",2);			//	落下してつぶれたときの音
//	LoadWave("script/spaha.wav",3);			//	main theme
	LoadWave("script/bokan.wav",4);			//	ショットがあたった
	LoadWave("script/gashaaa.wav",5);		//	ショットがあたった
	LoadMIDI("script/sharrier.mid");		//	メインテーマ
	TextLayerOn(1,20,20);				//	Scoreの表示レイヤ
	TextSize(1,16);
}

void 爆発表示(int px,int py,int x,int y,int z,int f){
	int xbuf,ybuf,zoom;
	zoom = 65536;
	xbuf = x;
	if( z != 0 ) {
		zoom = (120 << 16) / z;
	}
	xbuf = ((x - (px-240))* zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py-400)/2)* zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(6,xbuf,ybuf,0,(3 - f)*48,48,48,zoom*2,zoom*2);			//	０番のプレーンの(0,192)から48×48を表示
}

void 迷路表示(int px, int py, int x, int y, int z){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px -240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py-400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(9,xbuf,ybuf,0,0,100,100, zoom, zoom);	//	０番のプレーンの(0,48+n*48)から48×48を表示
	ybuf = (480 * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	if(z < 320){BltRectR(0,xbuf,ybuf,0,288,48,48,zoom,zoom);}	//	影を表示
}

void 草表示(int px, int py, int x, int y, int z){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px -240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((480 - (py-400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(10,xbuf,ybuf,0,0,128,128, zoom, zoom);	//	０番のプレーンの(0,48+n*48)から48×48を表示
}

void ライン表示(int px, int py, int x, int y, int z){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px -240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((96 - (py-400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(11,xbuf,ybuf,0,0,192,384, zoom, zoom);	//	０番のプレーンの(0,48+n*48)から48×48を表示
	ybuf = (480 * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	if(z < 320){BltRectR(0,xbuf,ybuf,0,288,48,48,zoom,zoom);}	//	影を表示
}

void マイキャラ表示(int x,int y){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / 80;
//	zoom = (120 << 16) / 120;
	x = x-12;
//	x = (x << 16 - (48 * zoom / 2)) >> 16;	// これだとー３６になってしまう。計算が何か違うはず
//	y = (y << 16 - (48 * zoom / 2)) >> 16;
//	xbuf = (x * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
//	ybuf = (y * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	xbuf=x; ybuf=y;
	BltRectR(0,xbuf,ybuf,0,0,48,48,zoom,zoom);				//	０番のプレーンの(0,0)から48×48を表示
	BltRectR(0,xbuf,400,0,288,48,48,zoom,zoom);				//	影を表示
}

void ブロック表示(int px, int py, int x,int y,int z,int n){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px - 240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py - 400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(0,xbuf,ybuf,0,n*48,48,48,zoom*2, zoom*2);			//	０番のプレーンの(0,48+n*48)から48×48を表示
	ybuf = (480 * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	if ( z < 240 ) { BltRectR(0,xbuf,ybuf,0,288,48,48,zoom*2,zoom*2); }				//	影を表示
}
void 弾表示(int px, int py, int x,int y,int z){
	int zoom,xbuf,ybuf;
	zoom=65536;
	if( z != 0 ) {
		zoom = (120 << 16) / z;
//		x = (x << 16 - (48 * zoom / 2)) >> 16;
	}
	xbuf = ((x - (px - 240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py - 400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(0,xbuf,ybuf,0,192,48,48,zoom,zoom);			//	０番のプレーンの(0,192)から48×48を表示
}

void ＢＧ表示(int bg,int x,int y){
	Blt(bg,((-x + 240) / 8) - 64, (y - 400) / 8 - 48);		//	１番のプレーンを表示
}

int 接触判定(int x1,int y1,int x3,int y3,int z3){
	int x2,x4,y2,y4;
	int z1,z2,z4;
	x2 = x1 + 40; y2 = y1 + 40;		//　主人公の矩形領域  :(x1,y1)-(x2,y2)
	x4 = x3 + 36; y4 = y3 + 36;		//	ブロックの矩形領域:(x3,y3)-(x4,y4)
	x1 = x1 + 8; y1 = y1 + 8;
	x3 = x3 + 12; y3 = y3 + 12;
	
	z1 = 100 + 16;
	z2 = 100 + 32;
	z4 = z3 + 32;
	z3 = z3 + 16;

	if( (x1 < x4) && (x3 < x2) && (y1 < y4) && (y3 < y2) ) {
		//	当たり！
		if( (z1 < z4) && (z3 < z2) ) {
			return 1;
		}
	}
	//	当たっていない！
	return 0;
}

int ショット判定(int px, int py,int x1,int y1,int z1,int x3,int y3,int z3,int width){
	int x2,x4,y2,y4,z2,z4, w1;
	w1 = width - 2;
	x2 = x1 + 36; y2 = y1 + 36; z2 = z1 + 36;	//　ショットの矩形領域  :(x1,y1)-(x2,y2)
	x4 = x3 - px + 240 + w1; y4 = y3 - (py - 400)/2 + w1; z4 = z3 + w1;	//	ブロックの矩形領域:(x3,y3)-(x4,y4)
	x1 = x1 + 12; y1 = y1 + 12; z1 = z1 + 12;
	x3 = x3 - px + 240 + 2; y3 = y3 - (py - 400)/2 + 2; z3 = z3 + 2;

	if( (x1 < x4) && (x3 < x2) && (y1 < y4) && (y3 < y2) && (z1 < z4) && (z3 < z2)) {
		//	当たり！
		return 1;
	}
	//	当たっていない！
	return 0;
}

void ゲームスタート表示(){
	ＢＧ表示(1,240,400);
	TextLayerOn(0,240,200);
	TextSize(0,36);
	TextOut(0,"push space\n");
	loop {
		KeyInput();
		if (IsPushSpaceKey()) break;
		halt;
	}
	TextLayerOff(0);
}

void ゲームオーバー表示(){
	TextLayerOn(0,50,200);
	TextSize(0,60);
	TextOut(0,"Ｇａｍｅ　Ｏｖｅｒ\nＰｒｅｓｓ　Ｅｓｃ\n");
	loop {
		KeyInput();
		if (IsPushEscKey()) break;
		halt;
	}
	TextLayerOff(0);
}

void マイキャラ移動(int* x,int* y,int* vx,int* vy,int* j){
	//	マイキャラの移動
	KeyInput();								//	キー入力
	*vx = 0;
	*vy = 0;
	if (IsPressLeftKey())  *vx = -12;	//	左が押されていれば速度は-8
	if (IsPressRightKey()) *vx =  8;	//	右が押されていれば速度は+8
	if (IsPressUpKey())  *vy = -12;		//	上が押されていれば速度は-8
	if (IsPressDownKey()) *vy =  8;		//	下が押されていれば速度は+8
	*x = *x + *vx;
	if (*x<0) *x = 0;					//	画面左端からは出れない
	if (*x>640-48) *x=640-48;			//	画面右端からは出れない

	*y = *y + *vy;
	if (*y<0) *y = 0;					//	画面上端からは出れない
	if (*y>400) *y=400;			//	画面下端からは出れない
}

void ブロック移動(int* bx,int* by,int* bz,int* bb){
	//	敵キャラの移動
	alt {
	case *bb == 1 : {
		//*bx = *bx - 8;						//	８ドットずつ左へ
		//if (*bx<-48) *bb = 0;				//	画面左に消えていればもう居ない
		*bz = *bz - 8;
		if(*bz <= 60) { *bz = 30; *bb=0; }
					}
	case *bb == 2 : {
		*by = *by + 8;						//	８ドットずつ下へ
		if (*by>=410) {						//	地面に衝突して潰れた
			*bb = 0;
			PlayWave(2);
		}
					}
	case *bb == 3 : {
		*bx = *bx - 8;
		*by = *by + 8;
		*bz = *bz - 8;
		if(*bz <= 60) { *bz = 30; *bb=0; }
		if (*bx<-48) *bb = 0;
		if (*by>=410) {
			*bb = 0;
			PlayWave(2);
		}
					}
	}
}
void 弾移動(int* tx,int* ty,int* tz,int* tvx,int* tvy,int* tvz,int* tt){
	*tx= *tx + *tvx;
	*ty= *ty + *tvy;
	*tz= *tz + *tvz;
	if (*tx>688) 	*tt = 0;
	if (*tx<-48) 	*tt = 0;
	if (*ty>=480)	*tt = 0;
	if (*ty<=-48)	*tt = 0;
	if (*tz>=480)	*tt = 0;
	if (*tz<=60)	*tt = 0;
}

void スコア表示(int* score, int* zanki){
	*score = *score + 10;
	sprintf(string[0],"SCORE : %.8d              - STAGE 01 -\n",*score);
	if(*zanki == 2)strcat(string[0],"●\n");
	if(*zanki == 3)strcat(string[0],"●●\n");
	TextOut(1,string[0]);
}

void ブロック発生(int* bx,int* by,int* bz,int* bb,int time){
	int r;
	//r = Rand(3) + 1; // １～３までの乱数を発生させる
	if(time < 300) return;
	r = ((time / 300)) % 3;
	if(r == 0) r = 3;
	alt {
	case r==1: { *bx = Rand(15)*48; *by = Rand(8)*48; *bz=480; }
	case r==2: { *bx = Rand(15)*48; *by = -48; *bz=200 + Rand(80); PlayWave(1); }
	case r==3: { *bx = Rand(15)*48+240; *by = -48; *bz=480; PlayWave(1); }
	}
	*bb = r;
}

void 壁発生(int* wx,int*wy,int*wz,int*ww,int time){
	*wx = Rand(6) * 100; *wy = (Rand(2)+1)*100; *wz=480; *ww = 1;
}

void 草発生(int* gx,int*gy,int*gz,int*gg,int time){
	*gx = Rand(100) * 6; *gy = (Rand(2)+1)*100; *gz=480; *gg = 1;
}

void ライン発生(int* lx,int*ly,int*lz,int*ll,int time){
	*lx = Rand(100) * 6; *ly = (Rand(2)+1)*100; *lz=480; *ll = 1;
}

void 弾発生(int x,int y,int bx,int by,int bz,int* tx,int* ty,int* tz,int* tvx,int* tvy,int* tvz,int* tt){
	int dx,dy,dz,dd;
	*tx = bx;
	*ty = by;
	*tz = bz;
	dx = x - bx;
	dy = y - by;
	dz = 100 - bz;	// キャラの座標は８０だが、狙いを少し甘くする。
	if(dz >= 0) return; 
	dd=0;
	if(dx >= 0)	dd = dd + dx;
	else		dd = dd - dx;
	if(dy >= 0)	dd = dd + dy;
	else		dd = dd - dy;
	if(dd<=100) return;			// 近すぎると弾を吐かない
	if(dz >= 0)	dd = dd + dz;
	else		dd = dd - dz;
	*tvx = (16 * dx) / (dd);
	*tvy = (16 * dy) / (dd);
	*tvz = (16 * dz) / (dd);
	*tt = 1;
}
