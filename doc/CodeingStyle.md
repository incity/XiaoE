# Header Files #
## Names and Order of Includes ##


# Naming #
## General Naming Rules ##
Names should be descriptive; avoid abbreviation.

Note that certain universally-known abbreviations are OK, such as i for an iteration variable and T for a template parameter.

As a rule of thumb, an abbreviation is probably OK if it's listed in Wikipedia.

### File Names ###
Do not use filenames that already exist in /usr/include, such as db.h.

### Type Names ###
type names start with a capital letter and have a capital letter for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.

### Variable Names ###
Data members of classes (but not structs) should start with a "m_" prefix.

The names of all types — classes, structs, type aliases, enums, and type template parameters — have the same naming convention. Type names should start with a capital letter and have a capital letter for each new word. No underscores.

# Formatting #
## Line Length ##
80 characters is the maximum.

A line may exceed 80 characters if it is


-  a comment line which is not feasible to split without harming readability, ease of cut and paste or auto-linking -- e.g. if a line contains an example command or a literal URL longer than 80 characters.
-  a raw-string literal with content that exceeds 80 characters. Except for test code, such literals should appear near the top of a file.
-  an include statement.
-  a header guard
-  a using-declaration

## Spaces vs. Tabs ##
Use only spaces, and indent 4 spaces at a time.

We use spaces for indentation. Do not use tabs in your code. You should set your editor to emit spaces when you hit the tab key.

## Namespace Formatting ##
The contents of namespaces are not indented.

Namespaces do not add an extra level of indentation. For example, use:

    namespace {

	void foo() {  // Correct.  No extra indentation within namespace.
	  ...
	}
	
	}  // namespace

Do not indent within a namespace.

When declaring nested namespaces, put each namespace on its own line.

    namespace foo {
	namespace bar {



	class Demo
	{
	// 1. public members
	public:
	        // 1.1. typedefs
	        // 1.2. enums
	        // 1.3. consts
	        // 1.4. constructors
	        // 1.5. destructors
	        // 1.6. member functions
	        // 1.7. member variables
	// 2. protected members
	protected:
	        // 2.1. typedefs
	        // 2.2. enums
	        // 2.3. consts
	        // 2.4. constructors
	        // 2.5. destructors
	        // 2.6. member functions
	        // 2.7. member variables
	
	// 3. protected members
	private:
	        // 3.1. typedefs
	        // 3.2. enums
	        // 3.3. consts
	        // 3.4. constructors
	        // 3.5. destructors
	        // 3.6. member functions
	        // 3.7. member variables
	};