#include <gtest/gtest.h>
#include "../src/morse/morse-alphabet.h"
#include "../src/morse/morse-translator.h"
#include "../src/morse/morse-types.h"

// Tests morse letter translations
TEST(LetterTranslation,MorseTests) {
  morse::MorseAlphabet alphabet;
  morse::MorseStringIterator s;
  char retranslated = '\0';
  for(char c='a'; c<='z'; ++c){
    s = alphabet.translateLetter(c);
    retranslated = alphabet.translateLetter(s);
    EXPECT_EQ(c,retranslated);
  }
  for(char c='0'; c<='9'; ++c){
    s = alphabet.translateLetter(c);
    retranslated = alphabet.translateLetter(s);
    EXPECT_EQ(c,retranslated);
  }
  EXPECT_THROW(alphabet.translateLetter('&'),std::invalid_argument);
}

TEST(TextTranslation, MorseTests){
  morse::MorseAlphabet alphabet;
  morse::MorseTranslate translate(alphabet);
  std::string expectedText = "the quick brown fox jumps over the lazy dog 0123456789";
  morse::MorseString expectedMorse = "- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / ..-. --- -..- / .--- ..- -- .--. ... / --- ...- . .-. / - .... . / .-.. .- --.. -.-- / -.. --- --. / ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.";
  morse::MorseString translationToMorse = translate.translateTextToMorse(expectedText);
  std::string translationToText = translate.translateMorseToText(expectedMorse);
  EXPECT_EQ(translationToMorse, expectedMorse);
  EXPECT_EQ(translationToText, expectedText);
}