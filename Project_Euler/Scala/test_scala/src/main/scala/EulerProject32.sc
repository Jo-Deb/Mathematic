val example = 1234
println(example)
example.toString
def nextValue(valour: Int) : Int = {
  var hauteur = 0
  var lastDigit = valour % 10
  var tmp = valour
  while( lastDigit == (9 - hauteur)){
    hauteur += 1
    tmp = tmp / 10
    lastDigit = tmp % 10
  }
  if ((lastDigit + 1) <= 9 - hauteur) {
    tmp = tmp / 10
    lastDigit += 1
    tmp = tmp * 10 + lastDigit
  }
  for(i <- 1 to hauteur){
      lastDigit += 1
      tmp = tmp * 10 + lastDigit
  }
  tmp
}
println(nextValue(1234)) // 1235
println(nextValue(1239)) // 1245
println(nextValue(1289)) // 1345
println(nextValue(1789)) // 2345
