// Generated from /Users/sadegh/Desktop/Personal/Programming Languages and Compilers/project/src/Smoola.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link SmoolaParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface SmoolaVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link SmoolaParser#prog}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProg(SmoolaParser.ProgContext ctx);
	/**
	 * Visit a parse tree produced by {@link SmoolaParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpr(SmoolaParser.ExprContext ctx);
}