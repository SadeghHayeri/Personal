// Generated from /Users/sadegh/Desktop/Personal/Programming Languages and Compilers/project/src/Smoola.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link SmoolaParser}.
 */
public interface SmoolaListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link SmoolaParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(SmoolaParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link SmoolaParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(SmoolaParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link SmoolaParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(SmoolaParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link SmoolaParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(SmoolaParser.ExprContext ctx);
}