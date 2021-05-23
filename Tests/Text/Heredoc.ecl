empty: |HEREDOC
HEREDOC

wsp: |EOF
	(	 	 )
	EOF

"one empty line": |HEREDOC

HEREDOC

|KEY
key
KEY
:|HEREDOC
string
HEREDOC

"Spoon Boy": |HEREDOC
      Do not try and bend the spoon, that's impossible.
      Instead, only try to realize the truth... there is no
      spoon. Then you'll see that it is not the spoon that
      bends, it is only yourself.
    HEREDOC

html: |html
	<!DOCTYPE html>
	<html>
	<body>
		<h2>Unordered List with Square Bullets</h2>

		<ul style="list-style-type:square;">
			<li>Coffee</li>
			<li>Tea</li>
			<li>Milk</li>
		</ul>

	</body>
	</html>
	html

markdown: |Markdown
    Heading
    =======

    ## Sub-heading

    Paragraphs are separated
    by a blank line.

    Two spaces at the end of a line  
    produces a line break.

    Text attributes _italic_, 
    **bold**, `monospace`.

    Horizontal rule:

    ---

    Bullet list:

      * apples
      * oranges
      * pears

    Numbered list:

      1. wash
      2. rinse
      3. repeat

    Markdown
