
void main(){
	int x,y;					//	�}�C�L�����̍��W��ێ����邽�߂̕ϐ�
	int vx,vy;					//	�}�C�L�����̑��x(�W�����v��)
	int j;						//	��i�W�����v�̂��߂̃t���O
	int bx[10],by[10],bz[10],bb[10];		//	�G�L�����̍��W�ƗL�����ǂ�����ێ����邽�߂̕ϐ�
	int wx[10],wy[10],wz[10],ww[10];		//	�ǂ̍��W
	int gx[10],gy[10],gz[10],gg[10];		//	���̍��W
	int lx[10],ly[10],lz[10],ll[10];		//	���C���̍��W
	//	bb[n]��0�Ȃ�΋󂫁A1�Ȃ�Ή��ړ����B2�Ȃ�Ώc�ړ����A3�Ȃ�Ύ΂߈ړ���\���B
	int tx[3],ty[3],tz[3],tvx[3],tvy[3],tvz[3],tt[3];
	int sx[3],sy[3],sz[3],st[3];			//	�V���b�g�ϐ�
	int score;
	int isDead;
	int i;
	int n;
	int tail;
	int bg;						//	�w�i�̎��
	int ii;
	int dragon;					//	�h���S���̏o��X�R�A
	int zoom,xbuf,ybuf;
	int ex[10],ey[10],ez[10],ee[10],ei;		//	�����p�ϐ�
	int zanki;
	int time;
	int zz;

	����������();
	�Q�[���X�^�[�g�\��();
	PlayMIDI();

	zanki = 3;
	score = 0;
	dragon = 50000;
	x = 240; y= 400;						//	�}�C�L�����̍��W������
	vx = 0;	 vy = 0;						//	�}�C�L�����̑��x�͂O
	j = 0;								//	�͂��߂̓W�����v���Ă��Ȃ�
	isDead = 0;							//	�ŏ��͐����Ă�

	for(i=0;i<10;i++) bb[i]=0;				//	�S�u���b�N������
	for(i=0;i<3;i++) tt[i]=0;				//	�e�̏�����
	for(i=0;i<3;i++) st[i]=0;				//	�V���b�g�̏�����
	for(i=0;i<10;i++) ee[i]=0;
	for(i=0;i<10;i++) ww[i]=0;				//	�Ǐ�����
	for(i=0;i<10;i++) gg[i]=0;				//	��������
	for(i=0;i<10;i++) ll[i]=0;				//	���C��������
	
	bx = 640; by = 400;					//	�G�L�����̍��W������
	bg=1;
	time=0;
	loop {
		time++;
		ClearSecondary();				//	��ʃN���A
//		���́A���ła�f��\������̂ŕs�v
		�a�f�\��(2,x,y);
		// Z-order��������艜�̂��̂��ɕ\��
		for(zz = 480; zz>0; zz--){
			if((ll[i] != 0) && (zz == lz[i])){
				���C���\��(x,y,lx[i],ly[i],lz[i]);
			}
			for(i=0;i<3;i++) {
				// �V���b�g�\��
				if((st[i] != 0) && (sz[i] == zz)) {
					zoom=65536;
					xbuf = x;
					if( sz[i] != 0 ) {
						zoom = (120 << 16) / sz[i];
					}
					xbuf = (sx[i] * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
					ybuf = (sy[i] * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
					BltRectR(0,xbuf,ybuf,0,240,48,48,zoom,zoom);			//	�O�Ԃ̃v���[����(0,192)����48�~48��\��
					sz[i] = sz[i] + 16;
					if(sz[i] > 480) {
						st[i] = 0;
					}
				}
			}
			for(i=0;i<10;i++){
				if((ee[i]!=0) && (ez[i] == zz)) {
					�����\��(x,y,ex[i],ey[i],ez[i],ee[i]);
					ee[i]--;
				}
			}
			for(i=0;i<10;i++){
				if((ww[i]!=0) && (wz[i] == zz)) { ���H�\��(x,y,wx[i],wy[i],wz[i]); }
			}
			for(i=0;i<10;i++){
				if((gg[i]!=0) && (gz[i] == zz)) { ���\��(x,y,gx[i],gy[i],gz[i]); }
			}
			for(i=0;i<10;i++){
				if ((bb[i]!=0) && (bz[i]==zz)) {
					�u���b�N�\��(x,y,bx[i],by[i],bz[i],bb[i]);
				}
			}
			for(i=0;i<3;i++){
				if (tt[i]!=0) {
					if(tz[i]==zz) {
						�e�\��(x,y,tx[i],ty[i],tz[i]);
					}
				}
			}
			if(zz==120){
				�}�C�L�����\��(x,y);
			}
		}
		// �V���b�g�̐ڐG����
		for(i=0;i<3;i++) {
			for(ii=0;ii<10;ii++){
				if(bb[ii]!=0) {
					if (�V���b�g����(x,y,sx[i],sy[i],sz[i],bx[ii],by[ii],bz[ii],96)){
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
					if (�V���b�g����(x,y,sx[i],sy[i],sz[i],wx[ii],wy[ii],wz[ii],100)){
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
					if (�V���b�g����(x,y,sx[i],sy[i],sz[i],lx[ii],ly[ii],lz[ii],100)){
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
		�}�C�L�����ړ�(&x,&y,&vx,&vy,&j);
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
			// ���C������
			if( ll[i]==0 ) {
				// 1/100�̊m���Ń��C������
				if (Rand(80) == 0) ���C������(&lx[i],&ly[i],&lz[i],&ll[i],time);
			}
			// ���C���ړ�
			lz[i] = lz[i] - 8;
			if(lz[i] <= 60) { lz[i] = 30; ll[i]=0; }
			if( ((i % 3) == 0) && ((ww[i]==0) && (ww[i+1]==0) &&(ww[i+2]==0) &&(ww[i+3]==0) &&(ww[i+4]==0))) {
				// 1/60�̊m���ŕǔ���
				if (Rand(60) == 0) {
					�ǔ���(&wx[i],&wy[i],&wz[i],&ww[i],time);
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
				// 1/100�̊m���ő�����
				if (Rand(100) == 0) ������(&gx[i],&gy[i],&gz[i],&gg[i],time);
			}
			// �ǈړ�
			wz[i] = wz[i] - 8;
			if(wz[i] <= 60) { wz[i] = 30; ww[i]=0; }
			// ���ړ�
			gz[i] = gz[i] - 8;
			if(gz[i] <= 60) { gz[i] = 30; gg[i]=0; }
			if ((bb[i]!=0)) {
				�u���b�N�ړ�(&bx[i],&by[i],&bz[i],&bb[i]);
				if (�ڐG����(x,y,bx[i],by[i],bz[i])) {isDead = 1;bb[i]=0;}	//	����
			} else {
			//	1/100�̊m���Ńu���b�N����
				if (Rand(100)==0) �u���b�N����(&bx[i],&by[i],&bz[i],&bb[i],time);
			}
		}
		for(i=0;i<3;i++){
			if (tt[i]!=0) {
				�e�ړ�(&tx[i],&ty[i],&tz[i],&tvx[i],&tvy[i],&tvz[i],&tt[i]);
				if (�ڐG����(x,y,tx[i],ty[i],tz[i])) {isDead = 1;tt[i]=0;}	//	����
			} else {
				for(ii=0;ii<10;ii++){
					// �e����
					if ((bb[ii]==2) || (bb[ii]==3)){
						if (Rand(100)==0) {
							�e����(x,y,bx[ii],by[ii],bz[ii],&tx[i],&ty[i],&tz[i],&tvx[i],&tvy[i],&tvz[i],&tt[i]);
						}
					}
				}
			}
		}
		�X�R�A�\��(&score,&zanki);

		halt;								//	��ʕ\��

		if (isDead) {
			PlayWave(5);
			ClearSecondary();					//	��ʃN���A
			halt;
			zanki--;
			isDead = 0;	// �����Ԃ�
			if(zanki==0){ break; }					//	����ł��H
		}
	}

	StopMIDI();
	�a�f�\��(2,x,y);
	�X�R�A�\��(&score,&zanki);
	�Q�[���I�[�o�[�\��();
}

void ����������(){
	SetFPS(30);					//	�t���[�����[�g���R�O��
	LoadBitmap("script/doli.bmp",0,1);		//	�h�b�g�̓ǂݍ���
	LoadBitmap("script/Space_Harrier_0.jpg",1,1);	//	BG2�̓ǂݍ���
	LoadBitmap("script/Space_Harrier_1.jpg",2,1);	//	BG2�̓ǂݍ���
	LoadBitmap("script/exp.bmp",6,1);		//	�h�b�g�̓ǂݍ���
	LoadBitmap("script/wall.bmp",9,1);		//	�ǉ摜�̓ǂݍ���
	LoadBitmap("script/glass.bmp",10,1);		//	���摜�̓ǂݍ���
	LoadBitmap("script/hline.bmp",11,1);		//	���C���摜�̓ǂݍ���
	LoadWave("script/hyupa2.wav",0);		//	�W�����v���̓ǂݍ���
	LoadWave("script/drop.wav",1);			//	�������̓ǂݍ���
	LoadWave("script/gucha.wav",2);			//	�������ĂԂꂽ�Ƃ��̉�
//	LoadWave("script/spaha.wav",3);			//	main theme
	LoadWave("script/bokan.wav",4);			//	�V���b�g����������
	LoadWave("script/gashaaa.wav",5);		//	�V���b�g����������
	LoadMIDI("script/sharrier.mid");		//	���C���e�[�}
	TextLayerOn(1,20,20);				//	Score�̕\�����C��
	TextSize(1,16);
}

void �����\��(int px,int py,int x,int y,int z,int f){
	int xbuf,ybuf,zoom;
	zoom = 65536;
	xbuf = x;
	if( z != 0 ) {
		zoom = (120 << 16) / z;
	}
	xbuf = ((x - (px-240))* zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py-400)/2)* zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(6,xbuf,ybuf,0,(3 - f)*48,48,48,zoom*2,zoom*2);			//	�O�Ԃ̃v���[����(0,192)����48�~48��\��
}

void ���H�\��(int px, int py, int x, int y, int z){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px -240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py-400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(9,xbuf,ybuf,0,0,100,100, zoom, zoom);	//	�O�Ԃ̃v���[����(0,48+n*48)����48�~48��\��
	ybuf = (480 * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	if(z < 320){BltRectR(0,xbuf,ybuf,0,288,48,48,zoom,zoom);}	//	�e��\��
}

void ���\��(int px, int py, int x, int y, int z){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px -240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((480 - (py-400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(10,xbuf,ybuf,0,0,128,128, zoom, zoom);	//	�O�Ԃ̃v���[����(0,48+n*48)����48�~48��\��
}

void ���C���\��(int px, int py, int x, int y, int z){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px -240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((96 - (py-400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(11,xbuf,ybuf,0,0,192,384, zoom, zoom);	//	�O�Ԃ̃v���[����(0,48+n*48)����48�~48��\��
	ybuf = (480 * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	if(z < 320){BltRectR(0,xbuf,ybuf,0,288,48,48,zoom,zoom);}	//	�e��\��
}

void �}�C�L�����\��(int x,int y){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / 80;
//	zoom = (120 << 16) / 120;
	x = x-12;
//	x = (x << 16 - (48 * zoom / 2)) >> 16;	// ���ꂾ�Ɓ[�R�U�ɂȂ��Ă��܂��B�v�Z�������Ⴄ�͂�
//	y = (y << 16 - (48 * zoom / 2)) >> 16;
//	xbuf = (x * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
//	ybuf = (y * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	xbuf=x; ybuf=y;
	BltRectR(0,xbuf,ybuf,0,0,48,48,zoom,zoom);				//	�O�Ԃ̃v���[����(0,0)����48�~48��\��
	BltRectR(0,xbuf,400,0,288,48,48,zoom,zoom);				//	�e��\��
}

void �u���b�N�\��(int px, int py, int x,int y,int z,int n){
	int zoom,xbuf,ybuf;
	zoom = (120 << 16) / z;
	xbuf = ((x - (px - 240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py - 400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(0,xbuf,ybuf,0,n*48,48,48,zoom*2, zoom*2);			//	�O�Ԃ̃v���[����(0,48+n*48)����48�~48��\��
	ybuf = (480 * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	if ( z < 240 ) { BltRectR(0,xbuf,ybuf,0,288,48,48,zoom*2,zoom*2); }				//	�e��\��
}
void �e�\��(int px, int py, int x,int y,int z){
	int zoom,xbuf,ybuf;
	zoom=65536;
	if( z != 0 ) {
		zoom = (120 << 16) / z;
//		x = (x << 16 - (48 * zoom / 2)) >> 16;
	}
	xbuf = ((x - (px - 240)) * zoom) >> 16 + ((640 - ((640 * zoom) >> 16)) / 2);
	ybuf = ((y - (py - 400) / 2) * zoom) >> 16 + ((480 - ((480 * zoom) >> 16)) / 2);
	BltRectR(0,xbuf,ybuf,0,192,48,48,zoom,zoom);			//	�O�Ԃ̃v���[����(0,192)����48�~48��\��
}

void �a�f�\��(int bg,int x,int y){
	Blt(bg,((-x + 240) / 8) - 64, (y - 400) / 8 - 48);		//	�P�Ԃ̃v���[����\��
}

int �ڐG����(int x1,int y1,int x3,int y3,int z3){
	int x2,x4,y2,y4;
	int z1,z2,z4;
	x2 = x1 + 40; y2 = y1 + 40;		//�@��l���̋�`�̈�  :(x1,y1)-(x2,y2)
	x4 = x3 + 36; y4 = y3 + 36;		//	�u���b�N�̋�`�̈�:(x3,y3)-(x4,y4)
	x1 = x1 + 8; y1 = y1 + 8;
	x3 = x3 + 12; y3 = y3 + 12;
	
	z1 = 100 + 16;
	z2 = 100 + 32;
	z4 = z3 + 32;
	z3 = z3 + 16;

	if( (x1 < x4) && (x3 < x2) && (y1 < y4) && (y3 < y2) ) {
		//	������I
		if( (z1 < z4) && (z3 < z2) ) {
			return 1;
		}
	}
	//	�������Ă��Ȃ��I
	return 0;
}

int �V���b�g����(int px, int py,int x1,int y1,int z1,int x3,int y3,int z3,int width){
	int x2,x4,y2,y4,z2,z4, w1;
	w1 = width - 2;
	x2 = x1 + 36; y2 = y1 + 36; z2 = z1 + 36;	//�@�V���b�g�̋�`�̈�  :(x1,y1)-(x2,y2)
	x4 = x3 - px + 240 + w1; y4 = y3 - (py - 400)/2 + w1; z4 = z3 + w1;	//	�u���b�N�̋�`�̈�:(x3,y3)-(x4,y4)
	x1 = x1 + 12; y1 = y1 + 12; z1 = z1 + 12;
	x3 = x3 - px + 240 + 2; y3 = y3 - (py - 400)/2 + 2; z3 = z3 + 2;

	if( (x1 < x4) && (x3 < x2) && (y1 < y4) && (y3 < y2) && (z1 < z4) && (z3 < z2)) {
		//	������I
		return 1;
	}
	//	�������Ă��Ȃ��I
	return 0;
}

void �Q�[���X�^�[�g�\��(){
	�a�f�\��(1,240,400);
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

void �Q�[���I�[�o�[�\��(){
	TextLayerOn(0,50,200);
	TextSize(0,60);
	TextOut(0,"�f�������@�n������\n�o���������@�d����\n");
	loop {
		KeyInput();
		if (IsPushEscKey()) break;
		halt;
	}
	TextLayerOff(0);
}

void �}�C�L�����ړ�(int* x,int* y,int* vx,int* vy,int* j){
	//	�}�C�L�����̈ړ�
	KeyInput();								//	�L�[����
	*vx = 0;
	*vy = 0;
	if (IsPressLeftKey())  *vx = -12;	//	����������Ă���Α��x��-8
	if (IsPressRightKey()) *vx =  8;	//	�E��������Ă���Α��x��+8
	if (IsPressUpKey())  *vy = -12;		//	�オ������Ă���Α��x��-8
	if (IsPressDownKey()) *vy =  8;		//	����������Ă���Α��x��+8
	*x = *x + *vx;
	if (*x<0) *x = 0;					//	��ʍ��[����͏o��Ȃ�
	if (*x>640-48) *x=640-48;			//	��ʉE�[����͏o��Ȃ�

	*y = *y + *vy;
	if (*y<0) *y = 0;					//	��ʏ�[����͏o��Ȃ�
	if (*y>400) *y=400;			//	��ʉ��[����͏o��Ȃ�
}

void �u���b�N�ړ�(int* bx,int* by,int* bz,int* bb){
	//	�G�L�����̈ړ�
	alt {
	case *bb == 1 : {
		//*bx = *bx - 8;						//	�W�h�b�g������
		//if (*bx<-48) *bb = 0;				//	��ʍ��ɏ����Ă���΂������Ȃ�
		*bz = *bz - 8;
		if(*bz <= 60) { *bz = 30; *bb=0; }
					}
	case *bb == 2 : {
		*by = *by + 8;						//	�W�h�b�g������
		if (*by>=410) {						//	�n�ʂɏՓ˂��Ēׂꂽ
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
void �e�ړ�(int* tx,int* ty,int* tz,int* tvx,int* tvy,int* tvz,int* tt){
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

void �X�R�A�\��(int* score, int* zanki){
	*score = *score + 10;
	sprintf(string[0],"SCORE : %.8d              - STAGE 01 -\n",*score);
	if(*zanki == 2)strcat(string[0],"��\n");
	if(*zanki == 3)strcat(string[0],"����\n");
	TextOut(1,string[0]);
}

void �u���b�N����(int* bx,int* by,int* bz,int* bb,int time){
	int r;
	//r = Rand(3) + 1; // �P�`�R�܂ł̗����𔭐�������
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

void �ǔ���(int* wx,int*wy,int*wz,int*ww,int time){
	*wx = Rand(6) * 100; *wy = (Rand(2)+1)*100; *wz=480; *ww = 1;
}

void ������(int* gx,int*gy,int*gz,int*gg,int time){
	*gx = Rand(100) * 6; *gy = (Rand(2)+1)*100; *gz=480; *gg = 1;
}

void ���C������(int* lx,int*ly,int*lz,int*ll,int time){
	*lx = Rand(100) * 6; *ly = (Rand(2)+1)*100; *lz=480; *ll = 1;
}

void �e����(int x,int y,int bx,int by,int bz,int* tx,int* ty,int* tz,int* tvx,int* tvy,int* tvz,int* tt){
	int dx,dy,dz,dd;
	*tx = bx;
	*ty = by;
	*tz = bz;
	dx = x - bx;
	dy = y - by;
	dz = 100 - bz;	// �L�����̍��W�͂W�O�����A�_���������Â�����B
	if(dz >= 0) return; 
	dd=0;
	if(dx >= 0)	dd = dd + dx;
	else		dd = dd - dx;
	if(dy >= 0)	dd = dd + dy;
	else		dd = dd - dy;
	if(dd<=100) return;			// �߂�����ƒe��f���Ȃ�
	if(dz >= 0)	dd = dd + dz;
	else		dd = dd - dz;
	*tvx = (16 * dx) / (dd);
	*tvy = (16 * dy) / (dd);
	*tvz = (16 * dz) / (dd);
	*tt = 1;
}
