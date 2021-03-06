#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
#include "Tinyfont.h"

// Low frame rate saves battery
#define FRAME_RATE 6

// Color array index
enum class ProgramState {
  SPLASH,
  CONFIG,
  VOTE,
  FIRST_PASS,
  PASS,
  TALLY
};

Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
ArduboyPlaytune tunes(arduboy.audio.enabled);


String planningPoker[] = { "", "", "", "start", "config", "last vote", "", "by Frederick Brunn"};
String capsPlanningPoker[] = { "", "", "", "START", "CONFIG", "LAST VOTE", "", "by Frederick Brunn"};

String cardPackTitles[] = {"fibonacci", "mountain goat", "sequential", "t-shirt sizes"};

int cardChoices[][12] = { { 1, 2, 3, 5, 8, 13, 21, 44, 65, 109, 176, -1 },
            { 0, 1, 2, 3, 5, 8, 13, 20, 40, 100, 200, -1 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
            { 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0 } };
            
String tShirtSizes[] = { "S", "M", "L", "XL", "2XL", "3XL"};

int cardCount[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const unsigned char PROGMEM splashImage[] = {126, 64, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0x80, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x71, 0x71, 0x7f, 0x3f, 0x3f, 0x1f, 0x0f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xf0, 0xff, 0xff, 0x8f, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xc7, 0x83, 0x83, 0x83, 0x83, 0xfb, 0xfb, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x01, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0xf3, 0xf0, 0xf0, 0xf3, 0xf3, 0xf3, 0xe3, 0xe3, 0xc0, 0x80, 0x03, 0x03, 0xc3, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf1, 0xe3, 0xe0, 0xc0, 0x00, 0x00, 0x01, 0xf1, 0xf3, 0xf3, 0xf3, 0xf3, 0x03, 0x03, 0x83, 0xe3, 0xf0, 0xf0, 0xe0, 0xe0, 0x20, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x87, 0x07, 0x87, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xfe, 0xff, 0xff, 0x9f, 0x07, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x73, 0x73, 0x73, 0x33, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0xbf, 0x3f, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x07, 0x06, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x01, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

ProgramState state = ProgramState::SPLASH;

int cursorLocation = 0;
int selectedCardPack = 0;
  int lastFrameTimer = 0;

// ============================= SETUP ===================================
void setup() {
  arduboy.boot();
  arduboy.systemButtons();
  Serial.begin(9600);
  arduboy.setFrameRate(FRAME_RATE);
    arduboy.setTextSize(1);

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
  #ifndef AB_DEVKIT
    // if not a DevKit
    tunes.initChannel(PIN_SPEAKER_2);
  #else
    // if it's a DevKit
    tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
    tunes.toneMutesScore(true);       // mute the score when a tone is sounding
  #endif
}
// =======================================================================


// =========================== MAIN LOOP =================================
void loop() {
  if (!arduboy.nextFrame()) {
  arduboy.idle();
    return;
  }
  arduboy.pollButtons();
  arduboy.clear();
  switch(state) {
    case ProgramState::SPLASH: {
    handleSplashInput();
    renderSplashScreen(lastFrameTimer);
  lastFrameTimer++;
  if(lastFrameTimer > 11) lastFrameTimer = 0;
    break;
    }
    case ProgramState::VOTE: {
    handleVoteInput();
    renderVoteScreen();
    break;
    }
    case ProgramState::PASS: {
    handlePassInput();
    renderPassScreen(true);
    cursorLocation = 0; // do it here so that we have rendered another screen before restoring the global to its default state.
    break;
    }
    case ProgramState::FIRST_PASS: {
    handlePassInput();
    renderPassScreen(false);
    break;
    }
    case ProgramState::TALLY: {
    handleTallyInput();
    renderTallyScreen();
    break;
    }
    default: {  // Default = CONFIG state; if we get here, there has been an issue, so let's do what we can to print useful debug info to Arduboy if applicable
    handleConfigInput();
    renderConfigScreen();
    break;
    }
  }
  arduboy.display();
  arduboy.idle();
}
// =======================================================================

void clearCardCounts() {
  for(int i = 0; i < 12; i++) {
  cardCount[i] = 0;
  }
}

void handleSplashInput(){
  if ((arduboy.pressed(UP_BUTTON) || arduboy.pressed(LEFT_BUTTON)) && cursorLocation > 0) {
    cursorLocation-=1;
    tunes.tone(1175,300);
  arduboy.idle();
  delay(FRAME_RATE);
  } else if ((arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(RIGHT_BUTTON)) && cursorLocation < 2) {
    cursorLocation+=1;
    tunes.tone(1397,300);
  arduboy.idle();
  delay(FRAME_RATE);
  } else if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
  switch(cursorLocation) {
    case 0: { // Start
      state = ProgramState::FIRST_PASS;
    clearCardCounts();
      cursorLocation = 0;
      break;
    }
    case 1: { // Config
      state = ProgramState::CONFIG;
      cursorLocation = 0;
      break;
    }
    case 2: { // Last Vote
      state = ProgramState::TALLY;
      cursorLocation = 0;
      break;
    }
  }
    tunes.tone(1397,300);
  arduboy.idle();
  delay(FRAME_RATE);
  }
}

void renderSplashScreen(int frameNumber){
  Sprites::drawOverwrite(0, frameNumber/6, splashImage, 0);
  for(int i = 0; i < 8; i++) {
    if(cursorLocation + 3 == i) {
      arduboy.print("* ");
      arduboy.println(capsPlanningPoker[i]);
    }
    else {
      arduboy.println(planningPoker[i]);
    }
  }
}

void handleVoteInput(){
  int numEntries = 12 - 3;
  if(selectedCardPack == 3) numEntries = 6 - 3;
  if (arduboy.pressed(UP_BUTTON) && (cursorLocation > 2)) {
    cursorLocation-=3;
  }
  else if (arduboy.pressed(DOWN_BUTTON) && (cursorLocation < numEntries)) {
    cursorLocation+=3;
  }
  else if (arduboy.pressed(LEFT_BUTTON) && (cursorLocation % 3 != 0)) {
    cursorLocation-=1;
  }
  else if (arduboy.pressed(RIGHT_BUTTON) && (cursorLocation % 3 != 2)) {
    cursorLocation+=1;
  }
  else if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
  cardCount[cursorLocation] = cardCount[cursorLocation] + 1;
    state = ProgramState::PASS;
  }
}

void renderVoteScreen(){
  int i = 0;
  if(selectedCardPack != 3) {
    if(cursorLocation > 5) {
    i += 6;
    arduboy.drawTriangle(42, 8, 46, 0, 50, 8);
    arduboy.drawTriangle(83, 8, 87, 0, 91, 8);
    }
    else {
    arduboy.drawTriangle(42, 55, 46, 62, 50, 55);
    arduboy.drawTriangle(83, 55, 87, 62, 91, 55);
    }
  }
  drawCard(7, 1, cardChoices[selectedCardPack][i++], i == cursorLocation);
  drawCard(48, 1, cardChoices[selectedCardPack][i++], i == cursorLocation);
  drawCard(89, 1, cardChoices[selectedCardPack][i++], i == cursorLocation);
  drawCard(7, 34, cardChoices[selectedCardPack][i++], i == cursorLocation);
  drawCard(48, 34, cardChoices[selectedCardPack][i++], i == cursorLocation);
  drawCard(89, 34, cardChoices[selectedCardPack][i], i == cursorLocation);
}

void drawCard(int x, int y, int rank, boolean selected) {
  int xPadding = 12;
  int yPadding = 4;
  if(rank < 9 && rank > 0) {
    arduboy.setTextSize(3);
  }
  else if(rank < 99) {
    arduboy.setTextSize(2);
    xPadding = 8;
  yPadding = 7;
  }
  else {
    arduboy.setTextSize(2);
    xPadding = 1;
  yPadding = 7;
  }
  
  if(selected) {
    arduboy.fillRoundRect(x, y, 38, 30, 6);
    arduboy.setTextColor(BLACK);
    arduboy.setTextBackground(WHITE);
  }
  
  if(selectedCardPack == 3) {
  arduboy.setCursor(x+2, y+7);
    arduboy.setTextSize(2);
  arduboy.print(tShirtSizes[rank]); // Kludge to get string-based card packs implemented
  }
  else {
  arduboy.setCursor(x+xPadding, y+yPadding);
  arduboy.print(rank);
  }
  
  if(!selected) {
    arduboy.drawRoundRect(x, y, 38, 30, 6);
  }
  else {
  arduboy.setTextColor(WHITE);
    arduboy.setTextBackground(BLACK);
  }
}

void handlePassInput(){
  if (arduboy.pressed(B_BUTTON)) {
    state = ProgramState::VOTE;
    cursorLocation = 0;
    tunes.tone(1397,300);
    arduboy.idle();
    delay(FRAME_RATE);
  }
  else if(arduboy.pressed(A_BUTTON)) {
    state = ProgramState::TALLY;
  }
}

void renderPassScreen(boolean previousVote){
  if(previousVote){
    arduboy.setTextSize(3);
    arduboy.setCursor(4, 4);
      arduboy.println("voted!");
  }
    arduboy.setTextSize(1);
    arduboy.println("next voter        (B)");
    arduboy.println("to end round   (A)");
}

void handleTallyInput(){
  int numEntries = 12 - 3;
  if(selectedCardPack == 3) numEntries = 6 - 3;
  
  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
  state = ProgramState::SPLASH;
      cursorLocation = 0;
  }
  else if ((arduboy.pressed(UP_BUTTON) || arduboy.pressed(LEFT_BUTTON)) && cursorLocation > 0) {
    cursorLocation-=1;
    tunes.tone(1175,300);
    arduboy.idle();
    delay(FRAME_RATE);
  } else if ((arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(RIGHT_BUTTON)) && cursorLocation < numEntries) {
    cursorLocation+=1;
    tunes.tone(1397,300);
    arduboy.idle();
    delay(FRAME_RATE);
  }
}

void renderTallyScreen(){
  drawCard(7, 1, cardChoices[selectedCardPack][cursorLocation], true);
  drawCard(48, 1, cardChoices[selectedCardPack][cursorLocation + 1], true);
  drawCard(89, 1, cardChoices[selectedCardPack][cursorLocation + 2], true);

  
  arduboy.setTextSize(2);
  arduboy.setCursor(7, 40);
  arduboy.print(cardCount[cursorLocation]);
  arduboy.setCursor(48, 40);
  arduboy.print(cardCount[cursorLocation+1]);
  arduboy.setCursor(89, 40);
  arduboy.print(cardCount[cursorLocation+2]);
  arduboy.setTextSize(1);
}

void handleConfigInput(){
  if (arduboy.pressed(A_BUTTON)) {
  state = ProgramState::SPLASH;
      cursorLocation = 0;
    return;
  }
  switch(cursorLocation) {
  case 0: {   
      if (arduboy.pressed(LEFT_BUTTON)) {
      selectedCardPack--;
      if(selectedCardPack < 0) {
        selectedCardPack = 3;
      }
      clearCardCounts();
      }   
      else if (arduboy.pressed(RIGHT_BUTTON)) {
      selectedCardPack++;
      if(selectedCardPack > 3) {
        selectedCardPack = 0;
      }
      clearCardCounts();
      }
    break;
  }
  default: {
    
  }
  }
}

void renderConfigScreen(){
  arduboy.print(F("card pack: "));
  arduboy.print(cardPackTitles[selectedCardPack]);
}
