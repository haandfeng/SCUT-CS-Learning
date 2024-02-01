def getNumbers(workingArray)
# Method to take multiple integers as input from user.
  puts "Please enter the numbers you'd like me to use. Type 'done' when you're finished."
  nextnum = 0
  # Creates nextnum as variable.
    while nextnum != "done"
      nextnum = gets.chomp!
        if nextnum == "done"
          puts "Calculating!"
        elsif nextnum != "0" && nextnum.to_i == 0
          # Checks for non-numerical characters.
          puts "That's not a number."
          nextnum = "done"
          # Breaks out of while loop if non-numerical character entered.
       else
          workingArray << nextnum.to_i
          # Stores each input as next value in workingArray.
      end
    end
end

def add(workingArray)
  # Defines method for addition.
  sum = 0
  # Creates variable sum.
  workingArray.each {|num| sum += num}
  # Sum increases by value of each item in array.
    puts "Your sum is #{sum}"
end

def subtract(workingArray)
  # Defines method for subtraction.
  dif = 0 + workingArray[0] + workingArray[0]
  # There are two of these to counteract the next step subtracting the first value.
  workingArray.each {|num| dif -= num}
  # Dif decreases by each item in array.
  puts "Your difference is #{dif}"
end

def multiply(workingArray)
  prod = 1
  # Begins variable prod at 1.
  workingArray.each {|num| prod *= num}
  # Prod multiplies by value of each item in array.
  puts "Your product is #{prod}"
end

def divide(workingArray)
  quot = 1 * workingArray[0] * workingArray[0]
  # Multiplies first val two times by first item in array...
  # to counteract first division by first val in array.
  workingArray.each {|num| quot /= num }
  # Quot divides by value of each item in array.
  puts "Your quotient is #{quot}"
end

# Running program begins here.
puts "Welcome to Calculator."
puts "Would you like to calculate something?"
puts "y/n"
firstIn = gets.chomp!.downcase

if firstIn == "n"
# If user answers "n", end program here.
  puts "That's too bad. Bye!"
end
if firstIn != "n" && firstIn != "y"
# If user types anything but "y" or "n", end program here.
  puts "I don't get it. Shutting down."
end

while firstIn == "y"
#if user enters yes, begin calc program loop.

workingArray = [] # Makes workingArray into an empty array.

puts "What operation would you like to perform?"
puts "Your options are: Add, Subtract, Multiply, Divide, Exponent, Square Root"
puts "Please enter your choice:"
choice = gets.chomp!.downcase
# User enters choice between calculator functions.

case choice
when "exponent"
# If user chooses exponent
  puts "Please enter the initial value (the one we'll be raising to a power)."
  starting_num = gets.chomp!
  # Gets first value, to be raised to a power.

  if starting_num != "0" && starting_num.to_i == 0
  # Checks for non-numerical characters.
    puts "Hey, that's not a number."
  else
    starting_num = starting_num.to_i
    # Converts this value into an integer.
    puts "Please enter the power you'd like to raise it to."
    # Gets power to raise starting_num to.
    power = gets.chomp!
    if power != "0" && power.to_i == 0
      puts "Hey, that's not a number."
    else
      power = power.to_i
      exp = starting_num ** power
      puts "Your exponent is #{exp}"
    end
  end

when "square root"
  puts "Please enter the number you'd like to find the square root of."
  to_square = gets.chomp!
  if to_square != "0" && to_square.to_i == 0
      puts "Hey, that's not a number."
  else
    to_square = to_square.to_i
    sqr = to_square ** (0.5)
    puts "Your square root is #{sqr}"
  end


when "add"
  getNumbers(workingArray)
  # Calls getNumbers function
  add(workingArray)

when "subtract"
  getNumbers(workingArray)
  # Calls getNumbers function
  subtract(workingArray)

when "multiply"
  getNumbers(workingArray)
  # Calls getNumbers function
  multiply(workingArray)

when "divide"
  getNumbers(workingArray)
  # Calls getNumbers function
  divide(workingArray)

else
  puts "That's not an option."
end

puts "Would you like to calculate something else?"
# Gives option to break out of while loop.
puts "y/n"
firstIn = gets.chomp.downcase
# Breaks while loop unless firstIn == y.

if firstIn == "n"
# Ends program.
  puts "k bye!"
end

if firstIn != "n" && firstIn != "y"
# Ends program.
  puts "I don't get it. Shutting down."
end

end



